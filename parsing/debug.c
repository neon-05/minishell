/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:43:26 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/25 17:45:10 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	show_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_putstr_fd(arr[i], 2);
		ft_putstr_fd("\t", 2);
		i++;
	}
	ft_putstr_fd("\n", 1);
}

void	show_t_parsed(t_parsed *parsed)
{
	printf(BLUE "\nIN T_PARSED** :\n\n" RESET);
	printf("INFILE:\n%s\n\n", parsed->infile);
	printf("OUTFILE:\n%s\n\n", parsed->outfile);
	printf("OUT_MODE:\n%s\n\n", parsed->out_mode);
	printf(BLUE "STR:" RESET);
	printf("\n");
	show_arr(parsed->split);
}
