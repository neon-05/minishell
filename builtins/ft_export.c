/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:12:59 by ylabussi          #+#    #+#             */
/*   Updated: 2025/03/04 16:00:08 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_export(char **args, char ***envp)
{
	if (arrlen((void **) args) < 2)
		return (1);
	return (setvar(args[1], envp));
}
