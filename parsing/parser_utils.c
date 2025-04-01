/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:29 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/31 15:58:06 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_ispaces(char **split, int i)
{
	if (!split[i])
		return (i);
	while (split[i] && ft_strnstr(split[i], " ", 2) != 0)
		i++;
	return i;
}

int	skip_ispaces_(char **split, int i)
{
	if (!split[i])
		return (i);
	while (i > 0 && split[i] && ft_strnstr(split[i], " ", 2) != 0)
		i--;
	return i;
}

char	*trimm(char *split)
{
	char	*temp;
	if (split[0] == '\'')
	{
		temp = ft_strtrim(split, "'");
		free(split);
		split = temp;
	}
	else if (split[0] == '"')
	{
		temp = ft_strtrim(split, "\"");
		free(split);
		split = temp;
	}
	return (split);
}
