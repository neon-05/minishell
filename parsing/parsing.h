/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:19:03 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/10 16:03:43 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//====================(INCLUDES)============================//
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../prompt/colors.h"

//====================(DEFINES)=============================//

typedef struct s_parsed
{
	char	**split;
	char	*infile;
	char	*outfile;
	char	*out_mode;
}	t_parsed;

//====================(STRUCTS)=============================//

//====================(DECLARATIONS)========================//

//parser
t_parsed	*parse(char **envp, char *rl);

//tokenizer
char		**tokenize(char *rl);

//limiter
int			limiter(char *limiter);

//struct
t_parsed	*struct_maker(char **split);

//parser_utils
char		**list_insert(char **lst1, char **lst2, int n);
void		duck_fishing(char **split, int i);
int			count_occ(char *str, int c);
int			total_occ(char **split, int c);
int			check_closed(char **split, int c, int n);
int			check_follow(char **split, char *c);

//debug
void		show_arr(char **arr);
void		show_t_parsed(t_parsed *parsed);

#endif
