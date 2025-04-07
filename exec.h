/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:19:51 by ylabussi          #+#    #+#             */
/*   Updated: 2025/04/07 15:02:46 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtins/builtins.h"
#include "minishell.h"

# define EXIT_SYSERROR 125
# define EXIT_PERMISSION 126
# define EXIT_NOT_FOUND 127

typedef struct s_parsed
{
	char			**split;
	char			*infile;
	char			*outfile;
	int				out_mode;
	struct s_parsed	*next;
	int				fds[2];
}	t_parsed;

size_t	arrlen(void **a);
int		idsep(char *s);
size_t	sepchr(char **a);
char	*pathcat(const char *path, const char *rel);
void	free_arr(void **arr, size_t l);
pid_t	exe_pipeline(t_parsed *cmd, char ***envp, int *status);

int		setvar(char const *var, char ***vars);
int		setvar_join(char const *prefix, char const *val, char ***vars);
int		delvar(char const *var, char ***vars);
size_t	getvarid(const char *var, size_t l, char **vars);
char	*getvar(char const *name, char **vars);
void	print_arr(char **arr, char *name);

#endif