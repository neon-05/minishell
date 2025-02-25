/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:37 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/25 21:32:41 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_var(char *str, char *path)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i - 1] != '$')
		i++;
	while (str[i + j] && str[i + j] != ' ' && ft_isalpha(str[i + j]))
		j++;
	new = ft_calloc(1, sizeof(char) * (ft_strlen(str) - j + ft_strlen(path) + 1));
	if (!new)
		return (NULL);
	ft_strlcat(new, str, i);
	ft_strlcat_mod(new, path, ft_strlen(path) + 1);
	ft_strlcat_mod(new, str + i + j, ft_strlen(str + i + j));
	new[ft_strlen(str) - j + ft_strlen(path) + 1] = '\0';
	return (new);
}

char	*get_syntax_error(char c)
{
	char	*str;


	str = ft_strjoin("bash: syntax error near unexpected token `", c);
	if (!str)
		return (NULL);
	str = ft_strjoin_f(str, "'");//check ??
	return (str);
}

int	is_problem_char(char *str)
{
	char	*error;

	if (str[0] == '\'' || str[0] == ')' \
		|| str[0] == '}' || str[0] == '<' || str[0] == '>')
	{
		error = get_syntax_error(str[0]);
		if (!error)
		{
			printf("ERROR");
			return (2);
		}
		ft_putstr_fd(error, 2);
		return (1);
	}
	return (0);
}

char	**handle_env(char **envp, char **split)
{
	char	*path;
	char	*temp;
	int	i;

	i = -1;
	path = NULL;
	while (split[++i])
	{
//		if (ft_strlen(ft_strchr(split[i], '$')) == 1 && ft_strnstr(ft_strchr(split[i], '$') + 1, "$$", 2) != 0)//a faire
//			path = get_envp(envp, "BASHPID=");
		while (split[i][0] != '\'' && count_occ(split[i], '$') != 0)
		{
			split[i] = ft_strtrim(split[i], "\"");//leaks
			if (i > 0 && ft_strnstr(split[i - 1], "<<", 3))// && i < size of split ?
				break ;
			path = get_envp(envp, ft_strchr(split[i], '$') + 1) + 1;
			if (find_envp(envp, ft_strchr(split[i], '$') + 1) == arr_size(envp))
				temp = replace_var(split[i], "");//free path
			else
				temp = replace_var(split[i], path);
			if (!temp)
				return (ft_free_arr(split, arr_size(split)), NULL);
			else
			{
				free(split[i]);
				split[i] = temp;
			}
		}
	}
	return (split);
}

char	**handle_redirections(char **split)
{
	int		i;
	int		fd;
	char	*temp;

	i = -1;
	while (split[++i])
	{
		if (i >= 1 && split[i + 1] && ft_strnstr(split[i], "<<<", 4))
		{
			if (split[i + 1] && is_problem_char(split[i + 1]) == 1)
			{
				if (is_problem_char(split[i + 1]) == 2)
					return (ft_free_arr(split, arr_size(split)), NULL);
				return (ft_free_arr(split, arr_size(split)), NULL);
			}
			duck_fishing(split, i);
			fd = open("./this_is_a_temporary_file_for_the_eof", O_CREAT | O_TRUNC | O_APPEND | O_WRONLY, 0777);//verifier que ca marche selon les droits de l'executable
			if (fd < 0)
				return (ft_free_arr(split, arr_size(split)), printf("Error opening files of LIMITER\n"), NULL);
			write(fd, split[i], ft_strlen(split[i]));
			temp = split[i];
			split[i] = "this_is_a_temporary_file_for_the_eof";
			free(temp);
		}
		else if (i >= 1 && split[i + 1] && ft_strnstr(split[i], "<<", 3))
		{
			if (split[i + 1] && is_problem_char(split[i + 1]))
				return (ft_free_arr(split, arr_size(split)), NULL);
			limiter(split[i + 1]);
			duck_fishing(split, i);
			temp = split[i];
			split[i] = "this_is_a_temporary_file_for_the_eof";
			free(temp);
		}
	}
	return (split);
}

t_parsed	*parse(char **envp, char *rl)
{

	char		**split;
	t_parsed	*parsed;

	split = tokenize(rl);
	if (!split)
		return (NULL);
	split = handle_env(envp, split);
	if (!split)
		return (printf("Error while handling env vars"), NULL);
	split = handle_redirections(split);
	if (!split)
		return (printf("Error while handling redirections"), NULL);
	parsed = struct_maker(split);
	show_t_parsed(parsed);
	return (parsed);
}





//WARNING  "echo \$HOME"	>>	"$HOME"











/*
int	init_token(t_token **token)
{
	(*token) = malloc(sizeof(t_token));
	if (!(*token))
		return (0);
	(*token)->str = NULL;
	(*token)->path = NULL;
	(*token)->is_cmd = 0;
	(*token)->is_d_quoted = 0;
	(*token)->is_quoted = 0;
	(*token)->next = NULL;
	return (1);
}

t_token	*list_const(char **envp, char **split)
{
	t_token	*lst;
	t_token	*current;
	int	i;

	if (!init_token(&lst))
		return (NULL);
	current = lst;
	i = -1;
	while (split[++i])
	{
		current->str = ft_strdup(split[i]);//check
		if (!current->str)
			return (NULL);
		current->path = get_path(envp, split[i]); //gerer pour enlever les "
		if (current->path != NULL)
			current->is_cmd = 1;
		if (!init_token(&(current->next)))
			return (NULL);//ft_free_t_token a faire
		current = current->next;
	}
	return (lst);
}

t_token	*parse(char **envp, char *rl)
{
	char	**split;
	t_token	*lst;

	lst = NULL;
	split = tokenize(rl);
	if (!split)
		return(NULL);
	lst = list_const(envp, split);
	return (ft_free_arr(split, arr_size(split)), lst);
}

*/
