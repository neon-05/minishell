/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:17:34 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/14 17:15:45 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
