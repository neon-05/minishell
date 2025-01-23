#include <stdio.h>
#include "minishell.h"

size_t	getvarid(const char *name, size_t l, char **vars);
char	*getvar(const char *name, char **vars);
size_t	addvar(char ***vars);
int		setvar(char ***vars, char const *var);
char	*format(char const *s, char **vars);
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

size_t	getvarid(const char *var, size_t l, char **vars)
{
	size_t	i;

	i = 0;
	while (vars[i] && (ft_strncmp(vars[i], var, l) || vars[i][l] != '='))
		i++;
	return (i);
}

char	*getvar(const char *name, char **vars)
{
	size_t	i;
	size_t	l;
	char	*r;

	r = getenv(name);
	if (r)
		return (r);
	l = idlen(name);
	i = getvarid(name, l, vars);
	if (vars[i])
		r = vars[i] + l + 1;
	return (r);
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

char	*format(char const *s, char **vars)
{
	size_t	newlen;
	size_t	start;
	size_t	i;
	char	*new;

	newlen = 0;
	i = 0;
	while (s[i])
	{
		start = i;
		while (s[i] && s[i] != '$')
			i++;
		newlen += i - start;
		i += (s[i] == '$');
		if (s[i])
			newlen += ft_strlen(getvar(s + i, vars));
		i += idlen(s + i);
	}
	new = malloc(newlen);
	if (!new)
		return (NULL);
	*new = '\0';
	printf("%li\n", newlen);
	i = 0;
	while (s[i])
	{
		start = i;
		while (s[i] && s[i] != '$')
			i++;
		i += (s[i] == '$');
		ft_strlcat(new, s + start, i + 1 - start);
	}
	return (new);
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

int main(int argc, char const *argv[])
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
		p = getvar(s + 1, vars);
		if (p)
			printf("%s\n", p);
	}
	else if (s[idlen(s)] == '=')
		setvar(&vars, s);
	else if (s[0] == '/')
	{
		p = format(s, vars);
		printf("%s\n", p);
		free(p);
	}
	print_arr(vars, "vars");
	i++;
	}
	freearr((void **) vars);
	return (0);
}
