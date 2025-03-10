/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:33:16 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/10 20:44:52 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "parsing.h"

void	clean_parsed(t_parsed *parsed)
{
	if (!parsed)
		return;
	if (parsed->split)
		ft_free_arr(parsed->split, arr_size(parsed->split));
	if (parsed->infile)
		free(parsed->infile);
	if (parsed->outfile)
		free(parsed->outfile);
	if (parsed)
		free(parsed);
}
