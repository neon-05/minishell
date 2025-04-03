/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:19:03 by malapoug          #+#    #+#             */
/*   Updated: 2025/04/03 01:47:47 by malapoug         ###   ########.fr       */
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

//====================(STRUCTS)=============================//
typedef struct s_parsed
{
	char			**split;
	char			*infile;
	char			*outfile;
	int				out_mode;
	struct s_parsed	*next;
}	t_parsed;



//====================(DECLARATIONS)========================//

//parser
t_parsed	*parse(char **envp, char *rl);
int			is_problem_char(char *str);

//tokenizer
char		**tokenize(char *rl);

//tokenizer_utils
char		**split_insert_arr(char ***split, int c);

//limiter
int			get_line(char **line);
int			limiter(char *limiter);

//struct
t_parsed	*struct_maker(char **split);

//in_and_out
int			remove_in_out(t_parsed *head);

//parser_utils
char		*trimm(char *split);

//tokenizer_utils
char		**list_insert(char **lst1, char **lst2, int n);
void		duck_fishing(char **split, int i);
int			count_occ(char *str, int c);
int			total_occ(char **split, int c);
int			check_closed(char **split, int n);
int			check_follow(char **split, char *c);

//clean
void	free_chain(t_parsed *head);

//debug
void		show_arr(char **arr);
void		show_t_parsed(t_parsed *parsed);

#endif
