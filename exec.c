/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:01:18 by ylabussi          #+#    #+#             */
/*   Updated: 2025/04/07 10:38:38 by ylabussi         ###   ########.fr       */
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
	printf("exe'd: %s\n", path);
	printf("PID =  %i\n", getpid());
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

pid_t	exe_cmd(t_parsed *cmd, char ***envp, int forkctl, int *status)
{
	if (cmd->infile)
		cmd->fds[0] = open(cmd->infile, O_RDONLY);
	if (cmd->outfile)
		cmd->fds[1] = open(cmd->outfile, cmd->out_mode | O_CREAT, 0666);
	if (forkctl || !is_builtin(cmd->split[0]))
		return (exe_cmd_fork(cmd, envp, status));
	else
		*status = exe_builtin(cmd->split, envp);
	return (0);
}

pid_t	exe_pipeline(t_parsed *cmd, char ***envp, int *status)
{
	pid_t	cpid;
	int		pfds[2];

	if (!cmd->next)
		return (exe_cmd(cmd, envp, 0, status));
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pfds))
				*status = EXIT_SYSERROR;
			else
			{
				cmd->fds[1] = pfds[1];
				cmd->next->fds[0] = pfds[0];
			}
		}
		cpid = exe_cmd(cmd, envp, 1, status);
		close(pfds[1]);
		cmd = cmd->next;
	}
	return (cpid);
}
