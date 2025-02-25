/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:19:03 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/25 13:32:24 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//====================(INCLUDES)============================//

# include "../minishell.h"

//====================(DEFINES)=============================//

typedef struct	t_parsed
{
	char	**split;
	char	*infile;
	char	*outfile;
}	s_parsed;

//====================(STRUCTS)=============================//

//====================(DECLARATIONS)========================//

//parser
char	**parse(char **envp, char *rl);

//tokenizer
char	**tokenize(char *rl);

//limiter
int	limiter(char *limiter);

//limiter
t_parsed	struct_maker(char **split);

//parser_utils
char	**list_insert(char **lst1, char **lst2, int n);
void	duck_fishing(char **split, int i);
int		count_occ(char *str, int c);
int		total_occ(char **split, int c);
int		check_closed(char **split, int c, int n);
int		check_follow(char **split, char *c);


#endif
