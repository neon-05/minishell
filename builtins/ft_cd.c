/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:47:21 by ylabussi          #+#    #+#             */
/*   Updated: 2025/04/07 14:25:03 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(char **args, char ***envp)
{
	char	*pwd;
	int		err;

	if (!args[1])
		return (EXIT_SYSERROR & chdir(getvar("HOME", *envp)));
	if (args[1][0] == '~')
	{
		args[1]+= 1 + (args[1][1] != '\0');
		chdir(getvar("HOME", *envp));
	}
	pwd = getcwd(NULL, 0);
	err = setvar_join("OLDPWD=", pwd, envp);
	free(pwd);
	if (err)
		return (EXIT_SYSERROR);
	if (chdir(args[1]))
		return (EXIT_SYSERROR);
	pwd = getcwd(NULL, 0);
	err = setvar_join("PWD=", pwd, envp);
	free(pwd);
	if (err)
		return (EXIT_SYSERROR);
	return (0);
}
