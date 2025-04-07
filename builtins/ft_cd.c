/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:47:21 by ylabussi          #+#    #+#             */
/*   Updated: 2025/04/07 11:13:16 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(char **args, char ***envp)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (setvar_join("OLDPWD=", pwd, envp))
	{
		free(pwd);
		return (EXIT_SYSERROR);
	}
	if (chdir(args[1]))
	{
		free(pwd);
		return (EXIT_SYSERROR);
	}
	free(pwd);
	pwd = getcwd(NULL, 0);
	if (setvar_join("PWD=", pwd, envp))
	{
		free(pwd);
		return (EXIT_SYSERROR);
	}
	free(pwd);
	return (0);
}
