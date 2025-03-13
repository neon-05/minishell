/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:29 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/13 02:29:36 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_ispaces(char **split, int i)
{
	if (!split[i])
		return (i);
	while (split[i] && (ft_strnstr(split[i], " ", 2) == 0 || ft_strnstr(split[i], "\"\"", 2) == 0))
		i++;
	return i;
}
