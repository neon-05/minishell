/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:01:18 by ylabussi          #+#    #+#             */
/*   Updated: 2025/04/09 17:41:21 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*find_exe(char *cmd, char **envp)
{
	char	**paths;
	char	*exe;
	size_t	i;

	i = 0;
	if (ft_strchr("/.~", cmd[0]))
		return (ft_strdup(cmd));
	paths = ft_split(getvar("PATH", envp), ':');
	if (!paths)
		return (NULL);
	exe = NULL;
	while (paths[i])
	{
		exe = pathcat(paths[i], cmd);
		i++;
		if (!exe)
			continue ;
		else if (access(exe, F_OK) == 0)
			break ;
		free(exe);
		exe = NULL;
	}
	free_arr((void **) paths, arrlen((void **) paths));
	return (exe);
}

int	exe_file(char *path, t_parsed *cmd, char **envp)
{
	if (!path)
		return (EXIT_SYSERROR);
	if (access(path, X_OK))
		return (EXIT_PERMISSION);
	execve(path, cmd->split, envp);
	return (EXIT_SYSERROR);
}

pid_t	exe_cmd_fork(t_parsed *cmd, char ***envp, int *status)
{
	pid_t	cpid;
	char	*path;

	path = find_exe(cmd->split[0], *envp);
	if (!path && !is_builtin(cmd->split[0]))
		return (-1);
	cpid = fork();
	if (cpid == -1)
		*status = EXIT_SYSERROR;
	else if (cpid == 0)
	{
		dup2(cmd->fds[0], 0);
		dup2(cmd->fds[1], 1);
		if (cmd->next)
			close(cmd->next->fds[0]);
		*status = exe_builtin(cmd->split, envp);
		if (*status == EXIT_NOT_FOUND)
			*status = exe_file(path, cmd, *envp);
		exit(*status);
	}
	if (path)
		free(path);
	return (cpid);
}

void	error(void)
{
	perror("msh");
}

pid_t	exe_cmd(t_parsed *cmd, char ***envp, int forkctl, int *status)
{
	if (cmd->infile)
		cmd->fds[0] = open(cmd->infile, O_RDONLY);
	if (cmd->outfile)
		cmd->fds[1] = open(cmd->outfile, cmd->out_mode | O_CREAT, 0666);
	if (cmd->fds[0] < 0 || cmd->fds[1] < 0)
	{
		*status = EXIT_SYSERROR;
		error();
		return (-1);
	}
	if (forkctl || !is_builtin(cmd->split[0]))
		return (exe_cmd_fork(cmd, envp, status));
	else
		*status = exe_builtin(cmd->split, envp);
	return (0);
}

void	exe_pipeline(t_parsed *cmd, char ***envp, int *status)
{
	pid_t	cpid;

	cpid = -1;
	if (!cmd->next)
		cpid = exe_cmd(cmd, envp, 0, status);
	else
	{
		while (cmd)
		{
			if (open_pipe(cmd))
			{
				*status = EXIT_SYSERROR;
				break ;
			}
			cpid = exe_cmd(cmd, envp, 1, status);
			close(cmd->fds[1]);
			cmd = cmd->next;
		}
	}
	if (cpid < 0)
		error();
	if (cpid > 0)
		waitpid(cpid, status, WUNTRACED);
	if (*status > 128)
		fprintf(stderr, "%s (core dumped)\n", strsignal(*status & 0X7F));
}
