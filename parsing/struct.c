/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:17:34 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/13 02:45:47 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*right_op(char **split, int i, char **out)
{
	char	*temp;

	if (ft_strnstr(split[i], ">", 2))
		temp = ft_strdup("O_WRONLY"); // check
	else
		temp= ft_strdup("O_APPEND"); // check
	duck_fishing(split, i);
	(*out) = ft_strjoin_f((*out), ","); // check ?
	(*out) = ft_strjoin((*out), split[i]); // check ?
	duck_fishing(split, i);
	return (temp);
}
int	remove_in_out(char **split, t_parsed *parsed)
{
	char	*mode;
	char	*out;
	int		i;

	parsed->infile = NULL;
	parsed->outfile = NULL;
	parsed->out_mode = NULL;
	parsed->split = NULL;
	out = NULL;
	mode = NULL;
	i = -1;
	while (split[++i])
	{
		if (arr_size(split) > 2 && split[i + 1] && ft_strnstr(split[i], "<", 2))
		{
			duck_fishing(split, i);
			i = skip_ispaces(split, i);
			parsed->infile = ft_strdup(split[i]);
			i = skip_ispaces(split, i);
			duck_fishing(split, i);
			i--;
		}
		else if (arr_size(split) > 2 && split[i + 1] \
				&& (ft_strnstr(split[i], ">>", 3) || ft_strnstr(split[i], ">", 2))) // >> = append  > = trunc
		{
			i = skip_ispaces(split, i);
			mode = ft_strjoin_f(mode, ","); // check ?
			mode = ft_strjoin_f(mode, right_op(split, i, &out)); // check ?
			i--;
		}
	}
	if (split[i - 1] && (ft_strnstr(split[i - 1], ">>", 2) || ft_strnstr(split[i - 1], "<", 2 || ft_strnstr(split[i - 1], ">", 2))))
	{
		printf("bash: syntax error near unexpected token `newline'"); // Mauvais input (c'est grave chef)
		return (0);
	}
	if (out && mode)
	{
		parsed->outfile = ft_split(out, ',');
		parsed->out_mode = ft_split(mode, ',');
	}
	free(out);
	free(mode);
	parsed->split = split;
	return (1);
}
/*
int	remove_in_out(char **split, t_parsed *parsed)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (arr_size(split) > 2 && split[i + 1] && ft_strnstr(split[i], "<", 2))
		{
			duck_fishing(split, i);
			i = skip_ispaces(split, i);
			parsed->infile = ft_strdup(split[i]);
			if (!parsed->infile)
				return (0); // leaks
			duck_fishing(split, i);
			i--;
		}
		else if (arr_size(split) > 2 && split[i + 1] \
				&& (ft_strnstr(split[i], ">>", 3) || ft_strnstr(split[i], ">", 2))) // >> = append  > = trunc
		{
			if (ft_strnstr(split[i], ">", 2))
				parsed->out_mode = ft_strdup("O_WRONLY"); // check
			else
				parsed->out_mode = ft_strdup("O_APPEND"); // check
			duck_fishing(split, i);
			i = skip_ispaces(split, i);
			parsed->outfile = ft_strdup(split[i]);
			duck_fishing(split, i);
			i--;
		}
	}
	return (1);
}

*/
t_parsed	*struct_maker(char **split)
{
	t_parsed	*parsed;

	parsed = malloc(sizeof(t_parsed));
	if (!parsed)
		return (printf("Error while creating struct\n"), NULL);
	if (!remove_in_out(split, parsed))
		return (printf("Error while creating struct\n"), NULL);
	return (parsed);
}
