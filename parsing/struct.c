/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:17:34 by malapoug          #+#    #+#             */
/*   Updated: 2025/03/17 19:52:51 by malapoug         ###   ########.fr       */
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

char	**cut_split(char **split)
{
	int	i;


	i = -1;
	while (split[++i])
	{
		if (ft_strnstr(split[i], "|", 2))
		{
			free(split[i]);
			split[i] = NULL;
			return (split + i);
		}
	}
	return (split + i);
}

void	init_node(char **split, t_parsed *node)
{
		node->split = split;
		node->infile = NULL;
		node->outfile = NULL;
		node->out_mode = NULL;
}

t_parsed	*create_chain(char **split, int n_node)
{
	t_parsed	*head;
	t_parsed	*temp;

	head = malloc(sizeof(t_parsed));
	if (!head)
		exit(0);
	temp = head;
	while (n_node > 0)
	{
		show_arr(split);
		temp->split = split;
		temp->infile = NULL;
		temp->outfile = NULL;
		temp->out_mode = NULL;
		split = cut_split(split + 1) + 1;
		temp->next = malloc(sizeof(t_parsed));
		if (!temp->next)
		{
			//free_chain();
			exit(0);
		}
		temp = temp->next;
		n_node--;
	}
	temp->next = NULL;
	return (head);
}

t_parsed	*struct_maker(char **split)
{
	t_parsed	*parsed;


	parsed = create_chain(split, count_pipes(split));
	if (!parsed)
		return (printf("Error while creating struct\n"), NULL);
	show_t_parsed(parsed);
//	if (!remove_in_out(split, parsed))
//		return (printf("Error while creating struct\n"), NULL);
	return (parsed);
}
