/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:06:44 by malapoug          #+#    #+#             */
/*   Updated: 2025/04/03 01:29:46 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_insert_arr(char ***split, int c)
{
	int		i;
	char	**temp;

	i = -1;
	while ((*split)[++i])
	{
		temp = ft_split_let((*split)[i], c);
		if (!temp)
			return (NULL); // free
		(*split) = list_insert((*split), temp, i);
		if (!split)
			return (NULL); // free
	}
	return (*split);
}

char	**full_split(char *rl)
{
	char	**split;

	split = ft_split_let(rl, '"');
	if (!split)
		return (NULL);
	split = split_insert_arr(&split, ' ');
	if (!split)
		return (ft_free_arr(split, arr_size(split)), NULL);
	split = split_insert_arr(&split, '\'');
	if (!split)
		return (ft_free_arr(split, arr_size(split)), NULL);
	split = split_insert_arr(&split, '|');
	if (!split)
		return (ft_free_arr(split, arr_size(split)), NULL);
	split = split_insert_arr(&split, ';');//enlever ?
	if (!split)
		return (ft_free_arr(split, arr_size(split)), NULL);
	split = split_insert_arr(&split, '>');
	if (!split)
		return (ft_free_arr(split, arr_size(split)), NULL);
	split = split_insert_arr(&split, '<');
	if (!split)
		return (ft_free_arr(split, arr_size(split)), NULL);
	return (split);
}

char	**full_join_sign(char **split)
{
	if (total_occ(split, '\"') % 2 != 0 || total_occ(split, '\'') % 2 != 0) // gerer " ' " '
		ft_putstr_fd(RED "[ツ] Unclosed quote !\n" RESET, 2);
	if (!check_closed(split, 2))
		return (NULL);
	if (!check_follow(split, "<"))
		return (NULL);
	if (!check_follow(split, ">"))
		return (NULL);
	if (!check_follow(split, "|"))
		return (NULL);
	if (!check_follow(split, "&"))
		return (NULL);
	if (!check_follow(split, "$"))
		return (NULL);
	return (split);
}

char	**tokenize(char *rl)
{
	char	**split;
	int		i;

	i = -1;
	split = full_split(rl);
	if (!split)
		return (NULL);
	split = full_join_sign(split);
	if (!split)
		return (NULL);
	while (split[++i])
	{
		if (ft_strncmp(split[i], " ", 2) == 0)
			duck_fishing(split, i--);// check ?
	}
	return (split);
}

//corriger les espaces vides!!  ==>> parsed->(char	*echo)

// ^^^^^ checker partout ^^^^^
