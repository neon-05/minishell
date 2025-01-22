/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:42:07 by malapoug          #+#    #+#             */
/*   Updated: 2025/01/22 17:01:50 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* assumes array is null-terminated */
size_t	arrlen(void **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

/* assumes array is null-terminated */
size_t	arrnlen(void **arr, size_t n)
{
	size_t	i;

	i = 0;
	while (arr[i] && i < n)
		i++;
	return (i);
}

void	ft_free_arr(void **arr, size_t i)
{
	while (i > 0)
		free(arr[--i]);
	free(arr);
}
