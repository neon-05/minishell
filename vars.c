/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabussi <ylabussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:03:15 by ylabussi          #+#    #+#             */
/*   Updated: 2025/04/07 11:09:25 by ylabussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

size_t	idlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] && !ft_strchr(METACHARSET, s[i]))
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

char	*getvar(char const *var, char **vars)
{
	size_t	i;
	size_t	l;
	char	*r;

	r = NULL;
	l = idlen(var);
	i = getvarid(var, l, vars);
	if (vars[i])
		r = vars[i] + l + 1;
	return (r);
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

int	setvar(char const *var, char ***vars)
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
		if (addvar(vars) > 0)
		{
			free(new);
			return (0);
		}
		else
			return (1);
		(*vars)[i] = new;
	}
	return (0);
}

int	setvar_join(char const *prefix, char const *val, char ***vars)
{
	size_t	i;
	char	*new;

	new = ft_strjoin(prefix, val);
	if (!new)
		return (1);
	i = getvarid(new, idlen(new), *vars);
	if ((*vars)[i])
	{
		free((*vars)[i]);
		(*vars)[i] = new;
	}
	else
	{
		if (addvar(vars) > 0)
		{
			free(new);
			return (0);
		}
		else
			return (1);
		(*vars)[i] = new;
	}
	return (0);
}

int	delvar(char const *var, char ***vars)
{
	size_t	l;
	size_t	arl;
	size_t	i;
	char	**new;

	arl = arrlen((void **) *vars);
	l = ft_strlen(var);
	i = getvarid(var, l, *vars);
	if (i == arl)
		return (0);
	new = ft_calloc(arl, sizeof(char *));
	if (!new)
		return (1);
	ft_memmove(new, *vars, i * sizeof(char *));
	ft_memmove(&new[i], &(*vars)[i + 1], (arl - i) * sizeof(char *));
	free((*vars)[i]);
	free(*vars);
	*vars = new;
	return (0);
}
