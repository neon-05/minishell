/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:17:34 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/25 17:30:53 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	remove_in_out(char **split, t_parsed *parsed)
{
	int		i;

	parsed->infile = NULL;
	parsed->outfile = NULL;
	parsed->out_mode = NULL;
	parsed->split = NULL;
	i = -1;
	while (split[++i])
	{
		if (arr_size(split) > 2 && split[i + 1] && ft_strnstr(split[i], "<", 2))
		{
			duck_fishing(split, i);
			parsed->infile = ft_strdup(split[i]);
			duck_fishing(split, i);
		}
		if (arr_size(split) > 2 && split[i + 1] && (ft_strnstr(split[i], ">>", 3) || ft_strnstr(split[i], ">", 2)))//			>> = append		> = trunc
		{
			if (ft_strnstr(split[i], ">>", 3))
				parsed->out_mode = "O_APPEND";
			else
				parsed->out_mode = "O_WRONLY";
			duck_fishing(split, i);
			parsed->outfile = ft_strdup(split[i]);
			duck_fishing(split, i);
		}
	}
	parsed->split = split;
	return (1);
}

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
