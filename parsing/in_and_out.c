/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_and_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:15:05 by malapoug          #+#    #+#             */
/*   Updated: 2025/04/03 16:15:06 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char **in(t_parsed *node, char **split)
{
	int		i;

	i = -1;
	while (split[++i])
	{
		if (ft_strnstr(split[i], "<", 2))
		{
			duck_fishing(split, i);
			if (!split[i] || (split[i] && is_problem_char(split[i]) == 1))
			{
				if (!split[i])
					printf("bash: syntax error near unexpected token `newline'");
				return (NULL);
			}
			node->infile = ft_strdup(split[i]); // check
			duck_fishing(split, i);
		}
		else if (ft_strnstr(split[i], "<<", 3))
		{
			duck_fishing(split, i);
			if (!split[i] || (split[i] && is_problem_char(split[i]) == 1))
			{
				if (!split[i])
					printf("bash: syntax error near unexpected token `newline'");
				return (NULL);
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
			if (!split[i] || (split[i] && is_problem_char(split[i]) == 1))
			{
				if (!split[i])
					printf("bash: syntax error near unexpected token `newline'");
				node->outfile = ft_strdup("/dev/null"); // check
				node->out_mode = O_WRONLY;
				continue;
			}
			node->outfile = ft_strdup(split[i]); // check
			node->out_mode = O_WRONLY;
			duck_fishing(split, i--);
		}
		else if (ft_strnstr(split[i], ">>", 3))
		{
			duck_fishing(split, i);
			if (!split[i] || (split[i] && is_problem_char(split[i]) == 1))
			{
				if (!split[i])
					printf("bash: syntax error near unexpected token `newline'");
				node->outfile = ft_strdup("/dev/null"); // check
				node->out_mode = O_APPEND;
				continue;
			}
			node->outfile = ft_strdup(split[i]); // check
			node->out_mode = O_APPEND;
			duck_fishing(split, i--);
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
