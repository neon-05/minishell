#include <stdio.h>
#include "minishell.h"

size_t	getvarid(const char *var, size_t vlen, char **vars);
char	*getvar(const char *var, size_t vlen, char **vars);
size_t	addvar(char ***vars);
int		setvar(char ***vars, char const *var);
char	*format(char **s, char **vars);
size_t	idlen(char const *s);

void	print_arr(char **arr, char *name)
{
	size_t	i;

	i = 0;
	printf("%s[%li]\n", name, arrlen((void **) arr));
	while (arr[i])
	{
		printf("[%li] -> %s\n", i, arr[i]);
		i++;
	}
	printf("\n");
}

size_t	idlen(char const *s)
{
	size_t i;

	i = 0;
	while(!ismetachar(s[i]))
		i++;
	return (i);
}

size_t	getvarid(const char *var, size_t vlen, char **vars)
{
	size_t	i;

	i = 0;
	while (vars[i] && (ft_strncmp(vars[i], var, vlen) || vars[i][vlen] != '='))
		i++;
	return (i);
}

char	*getvar(const char *var, size_t vlen, char **vars)
{
	size_t	i;

	i = getvarid(var, vlen, vars);
	if (vars[i])
		return (vars[i] + vlen + 1);
	else
		return (NULL);
}

int	setvar(char ***vars, char const *var)
{
	size_t	i;
	char	*new;

	new = ft_strdup((char *) var);
	if (!new)
		return (1);
	i = getvarid(var, idlen(var), *vars);
	if ((*vars)[i])
	{
		free((*vars)[i]);
		(*vars)[i] = new;
	}
	else
	{
		if(addvar(vars) == 0)
		{
			free(new);
			return (0);
		}
		(*vars)[i] = new;
	}
	return (0);
}

size_t	addvar(char ***vars)
{
	size_t	i;
	char	**new;

	i = 0;
	while ((*vars)[i])
		i++;
	i++;
	new = ft_calloc(i + 2, sizeof(char *));
	if (!new)
		return (0);
	ft_memmove(new, *vars, i * sizeof(char *));
	free(*vars);
	new[i + 1] = NULL;
	*vars = new;
	return (i);
}

int main(int argc, char const *argv[], char **envp)
{
	int			i;
	char const	*s;
	char		*p;
	char		**vars;

	vars = malloc(sizeof(char *));
	if (!vars)
		return (1);
	*vars = NULL;
	i = 1;
	if (argc < 2)
		return (1);
	while (i < argc)
	{
	s = argv[i];
	if (s[0] == '$')
	{
		p = getenv(s + 1);
		if (!p)
			p = getvar(s + 1, idlen(s + 1), vars);
		if (p)
			printf("%s\n", p);
	}
	else if (s[idlen(s)] == '=')
		setvar(&vars, s);
	i++;
	print_arr(vars, "vars");
	}
	ft_free_arr((void **) vars, arrlen((void **) vars));
	envp++;
	return (0);
}
