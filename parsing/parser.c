/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:37 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/28 20:22:09 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_var(char *str, char *path)
{
	char	*n;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i - 1] != '$')
		i++;
	while (str[i + j] && str[i + j] != ' ' && ft_isalpha(str[i + j]))
		j++;
	n = ft_calloc(1, sizeof(char) * (ft_strlen(str) - j + ft_strlen(path) + 1));
	if (!n)
		return (NULL);
	ft_strlcat(n, str, i);
	ft_strlcat_mod(n, path, ft_strlen(path) + 1);
	ft_strlcat_mod(n, str + i + j, ft_strlen(str + i + j));
	n[ft_strlen(str) - j + ft_strlen(path) + 1] = '\0';
	return (n);
}

int	is_problem_char(char *str)
{
	if (str[0] == '\'' || str[0] == ')' \
		|| str[0] == '}' || str[0] == '<' || str[0] == '>')
	{
		printf("bash: syntax error near unexpected token `%c'\n", (str[0])); // pas le bon fd (c'est grave chef?)
		return (1);
	}
	return (0);
}

char	**handle_env(char **envp, char **split)
{
	int		i;
	char	*path;
	char	*temp;

	i = -1;
	path = NULL;
	while (split[++i])
	{
		while (split[i][0] != '\'' && count_occ(split[i], '$') != 0)
		{
			if (split[skip_ispaces_(split, i - 1)] && ft_strnstr(split[skip_ispaces_(split, i - 1)], "<<", 3) && !ft_strnstr(split[skip_ispaces_(split, i - 1)], "<<<", 4))
				break ;
			path = get_envp(envp, ft_strchr(split[skip_ispaces(split, i)], '$') + 1) + 1;//check
			if (find_envp(envp, ft_strchr(split[skip_ispaces(split, i)], '$') + 1) == arr_size(envp))
				temp = replace_var(split[skip_ispaces(split, i)], "");//free path
			else
				temp = replace_var(split[skip_ispaces(split, i)], path);
			if (!temp)
				return (ft_free_arr(split, arr_size(split)), NULL);
			free(split[skip_ispaces(split, i)]);
			split[skip_ispaces(split, i)] = temp;
			split = list_insert(split, tokenize(split[skip_ispaces(split, i)]), skip_ispaces(split, i)); // check
		}
	}
	return (split);
}
//			if (ft_strnstr(split[i], "$$", 3))
//			{
//				free(split[i]);
//				split[i] = ft_strdup("$BASHPID"); //Faut rajouter le PID dans les env que yoan cree
//			}

char	**handle_redirections(char **split)
{
	int		i;
	int		fd;

	i = -1;
	while (split[++i])
	{
		if (ft_strnstr(split[i], "<<<", 4))
		{
			i = skip_ispaces(split, i + 1);
			if (!split[i] || (split[i] && is_problem_char(split[i]) == 1))
			{
				if (!split[i])
					printf("bash: syntax error near unexpected token `newline'");
				ft_free_arr(split, arr_size(split));
				exit(2);
			}
			fd = open("./this_is_a_temporary_file_for_the_eof", O_CREAT | O_TRUNC | O_APPEND | O_WRONLY, 0777);//verifier que ca marche selon les droits de l'executable
			if (fd < 0)
				return (ft_free_arr(split, arr_size(split)), printf("Error opening files of LIMITER\n"), NULL);
			write(fd, split[i], ft_strlen(split[i])); //check
			close(fd);
			free(split[i]);
			split[i] = ft_strdup("this_is_a_temporary_file_for_the_eof");
			if (!split[i])
				return (ft_free_arr(split, arr_size(split)), NULL);
		}
		else if (ft_strnstr(split[i], "<<", 3))
		{
			i = skip_ispaces(split, i + 1);
			if (!split[i] || (split[i] && is_problem_char(split[i]) == 1))
			{
				if (!split[i])
					printf("bash: syntax error near unexpected token `newline'");
				ft_free_arr(split, arr_size(split));
				exit(2);
			}
			limiter(split[i]);
			split[i] = ft_strdup("this_is_a_temporary_file_for_the_eof");
			if (!split[i])
				return (ft_free_arr(split, arr_size(split)), NULL);
		}
	}
	return (split);
}

void	trimm(char **split)
{
	char	*temp;
	int		i;

	i = -1;
	while (split[++i])
	{
		if (split[i][0] == '\'')
		{
			temp = ft_strtrim(split[i], "'");
			free(split[i]);
			split[i] = temp;
		}
		else if (split[i][0] == '"')
		{
			temp = ft_strtrim(split[i], "\"");
			free(split[i]);
			split[i] = temp;
		}
	}
}

t_parsed	*parse(char **envp, char *rl)
{
	char		**split;
	t_parsed	*parsed;

	(void)envp;
	split = tokenize(rl);
	if (!split)
		return (printf("Error while tokenizing\n"), NULL);
	split = handle_env(envp, split);
	if (!split)
		return (printf("Error while handling env vars\n"), NULL);//free inside
	split = handle_redirections(split);
	if (!split)
		return (printf("Error while handling redirects\n"), NULL);//free inside
	parsed = struct_maker(split);
	if (!parsed)
		return (NULL);//free inside
//	trimm(parsed->split);
	show_t_parsed(parsed);
return (parsed);
}

//WARNING  "echo \$HOME"	>>	"$HOME"
