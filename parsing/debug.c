/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:43:26 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/13 02:03:09 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	show_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
	{
		printf("(null)\n");
		return;
	}
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
	printf("OUTFILE:\n");
	show_arr(parsed->outfile);
	printf("\nOUT_MODE:\n");
	show_arr(parsed->out_mode);
	printf(BLUE "\nSTR:" RESET);
	printf("\n");
	show_arr(parsed->split);
}
