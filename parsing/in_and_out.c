/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_and_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:15:05 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/18 16:36:12 by malapoug         ###   ########.fr       */
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

char **in(t_parsed *node, char **split)
{
	int		i;

	i = -1;
	while (split[++i])
	{
		if (ft_strnstr(split[i], "<", 2))
		{
			duck_fishing(split, i);
			i = skip_ispaces(split, i);
			if (!split[i] || (split[i] && is_problem_char(split[i]) == 1))
			{
				if (!split[i])
					printf("bash: syntax error near unexpected token `newline'");
				ft_free_arr(split, arr_size(split));
				exit(2);
			}
			node->infile = ft_strdup(split[i]); // check
			duck_fishing(split, i);
		}
		else if (ft_strnstr(split[i], "<<", 3))
		{
			duck_fishing(split, i);
			i = skip_ispaces(split, i);
			if (!split[i] || (split[i] && is_problem_char(split[i]) == 1))
			{
				if (!split[i])
					printf("bash: syntax error near unexpected token `newline'");
				ft_free_arr(split, arr_size(split));
				exit(2);
			}
		}
	}
	return (split);
}

char **out(t_parsed *node, char **split)
{
	int		i;

	i = -1;
	while (split[++i])
	{
		if (ft_strnstr(split[i], ">", 2))
		{
			duck_fishing(split, i);
			i = skip_ispaces(split, i);
			if (!split[i] || (split[i] && is_problem_char(split[i]) == 1))
			{
				if (!split[i])
					printf("bash: syntax error near unexpected token `newline'");
				ft_free_arr(split, arr_size(split));
				exit(2);
			}
			node->outfile = ft_strdup(split[i]); // check
			node->out_mode = ft_strdup("O_WRONLY"); // check
			duck_fishing(split, i);
		}
		else if (ft_strnstr(split[i], ">>", 3))
		{
			duck_fishing(split, i);
			i = skip_ispaces(split, i);
			if (!split[i] || (split[i] && is_problem_char(split[i]) == 1))
			{
				if (!split[i])
					printf("bash: syntax error near unexpected token `newline'");
				ft_free_arr(split, arr_size(split));
				exit(2);
			}
			node->outfile = ft_strdup(split[i]); // check
			node->out_mode = ft_strdup("O_APPEND"); // check
			duck_fishing(split, i);
		}
	}
	return (split);
}

int	remove_in_out(t_parsed *head)
{
	t_parsed	*temp;

	temp = head;
	while (temp)
	{
		temp->split = in(temp, temp->split);
		temp->split = out(temp, temp->split);
		temp = temp->next;
	}
	return (1);
}
