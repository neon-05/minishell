/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:20:03 by ylabussi          #+#    #+#             */
/*   Updated: 2025/04/07 10:23:47 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

size_t	arrlen(void **a)
{
	size_t	i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

void	free_arr(void **arr, size_t l)
{
	while (l > 0)
		free(arr[--l]);
	free(arr);
}

char	*pathcat(const char *path, const char *rel)
{
	size_t	len;
	int		addsep;
	char	*new;

	len = ft_strlen(path);
	addsep = (path[len - 1] != '/');
	if (addsep)
		len++;
	len += ft_strlen(rel);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, path, len + 1);
	ft_strlcat(new, "/", len + 1);
	ft_strlcat(new, rel, len + 1);
	return (new);
}
