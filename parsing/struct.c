/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:17:34 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/25 15:56:59 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	remove_in_out(char **split, t_parsed *parsed)
{
	int		i;
	char	*temp;

	(void)parsed;
	i = -1;
	while (split[++i])
	{
		if (arr_size(split) > 2 && split[i + 1] && ft_strnstr(split[i], "<", 2))
		{
			duck_fishing(split, i);
			temp = split[i];
			split[i] = split[i + 1];
			split[i + 1] = temp;

		}
	}
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
