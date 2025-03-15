/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_and_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:15:05 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/14 19:48:42 by malapoug         ###   ########.fr       */
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

int	in_and_out(char **split)
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



char **in_and_out(char **split, t_parsed *parsed)
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
			parsed->infile = ft_strdup(split[i]); // check
			duck_fishing(split, i);
			i = skip_ispaces(split, i);
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
}
