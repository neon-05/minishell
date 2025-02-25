/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:19:03 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/25 16:49:33 by malapoug         ###   ########.fr       */
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

//====================(DEFINES)=============================//

typedef struct	s_parsed
{
	char	**split;
	char	*infile;
	char	*outfile;
	char	*out_mode;
}	t_parsed;

//====================(STRUCTS)=============================//

//====================(DECLARATIONS)========================//

//parser
char	**parse(char **envp, char *rl);

//tokenizer
char	**tokenize(char *rl);

//limiter
int	limiter(char *limiter);

//struct
t_parsed	*struct_maker(char **split);

//parser_utils
char	**list_insert(char **lst1, char **lst2, int n);
void	duck_fishing(char **split, int i);
int		count_occ(char *str, int c);
int		total_occ(char **split, int c);
int		check_closed(char **split, int c, int n);
int		check_follow(char **split, char *c);


#endif
