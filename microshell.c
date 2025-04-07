/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:01:46 by ylabussi          #+#    #+#             */
/*   Updated: 2025/04/07 11:11:18 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

char	**arrdup(char **arr)
{
	size_t	i;
	size_t	alen;
	char	**new;

	i = 0;
	alen = arrlen((void **) arr);
	new = malloc((alen + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (i < alen)
	{
		new[i] = ft_strdup(arr[i]);
		if (!new[i])
			break ;
		i++;
	}
	new[alen] = NULL;
	if (i < alen)
	{
		free_arr((void **)new, i);
		return (NULL);
	}
	return (new);
}

void	sa(int sig)
{
	fprintf(stderr, "caught signal %i\n", sig);
}

int	main(int argc, char **argv, char **envp)
{
	char		*arg1[] = {"cd", "libft", NULL};
	char		*arg2[] = {"pwd", NULL};
	t_parsed	cmd2 = {.fds = {0,1}, .split = arg2, .next = NULL, .infile = NULL, .outfile = NULL};
	t_parsed	cmd1 = {.fds = {0,1}, .split = arg1, .next = NULL, .infile = NULL, .outfile = NULL};
	char		**e = arrdup(envp);
	if (!e)
		return (-1);
	int		status;
	pid_t	cpid;
	signal(SIGINT, sa);
	signal(SIGQUIT, sa);
	
	cpid = exe_pipeline(&cmd1, &e, &status);
	if (cpid)
		waitpid(cpid, &status, 0);
	cpid = exe_pipeline(&cmd2, &e, &status);
	if (cpid)
		waitpid(cpid, &status, 0);
	free_arr((void **)e, arrlen((void **)e));
	printf("exit status - %i\n", status);
	return (0);
	cmd2.fds[0]++;
	argc++;
	argv++;
}