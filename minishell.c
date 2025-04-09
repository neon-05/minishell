/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:01:46 by ylabussi          #+#    #+#             */
/*   Updated: 2025/04/09 17:38:35 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	write(STDERR_FILENO, "\n", 1);
	sig++;
}

int	main(int argc, char **argv, char **envp)
{
	char		*arg1[] = {"cat", "-e", NULL};
	char		*arg2[] = {"cat", "-e", NULL};
	t_parsed	cmd2 = {.fds = {0,1}, .split = arg2, .next = NULL, .infile = NULL, .outfile = NULL, .out_mode = O_WRONLY};
	t_parsed	cmd1 = {.fds = {0,1}, .split = arg1, .next = NULL, .infile = NULL, .outfile = NULL, .out_mode = O_WRONLY};
	char		**e = arrdup(envp);
	if (!e)
		return (-1);
	int		status;
	signal(SIGINT, sa);
	signal(SIGQUIT, sa);
	exe_pipeline(&cmd1, &e, &status);
	fprintf(stderr, "exit status - %i\n", status);
	free_arr((void **)e, arrlen((void **)e));
	return (0);
	cmd2.fds[0]++;
	argc++;
	argv++;
}
