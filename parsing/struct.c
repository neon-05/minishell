/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:17:34 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/17 01:12:20 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


int	count_pipes(char **split)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (split[++i])
	{
		if (ft_strnstr(split[i], "|", 2))
			count++;
	}
	return (count);
}

char	**cut_split(t_parsed *temp, char **split)
{
	int	i;

	i = 0;
	while (split[++i])
	{
		if (ft_strnstr(split[i], "|", 2))

	}

	return (split);
}

t_parsed	*create_chain(char **split, int n_node)
{
	t_parsed	*head;
	t_parsed	*temp;

	head = malloc(sizeof(t_parsed));
	if (!head)
	{
		//free_chain();
		exit(0);
	}
	temp = head;
	while (n_node > 0)
	{
		split = cut_split(temp, split);
		temp->next = malloc(sizeof(t_parsed));
		if (!temp->next)
		{
			//free_chain();
			exit(0);
		}
		temp = temp->next;
		n_node--;
	}
}

t_parsed	*struct_maker(char **split)
{
	t_parsed	*parsed;

	parsed = create_chain(split, count_pipes(split));
//	if (!remove_in_out(split, parsed))
//		return (printf("Error while creating struct\n"), NULL);
	return (parsed);
}
