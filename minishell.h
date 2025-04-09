/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:00:12 by ylabussi          #+#    #+#             */
/*   Updated: 2025/04/09 14:54:30 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <sys/wait.h>
# include "exec.h"

# define METACHARSET "<>|?*[]$\\(){}\"'`&;=! "

void	dellast(t_list *lst, void (*del)(void*));
int		manage_dir(t_list **path, char *str, size_t len);
int		follow_path(t_list **path, char *rel);
char	*lst_to_str(t_list *lst);
char	*relative_path(char *from, char *to, char *home);

#endif
