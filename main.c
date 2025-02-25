/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malapoug <malapoug@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:24:35 by malapoug          #+#    #+#             */
/*   Updated: 2025/02/25 21:30:25 by malapoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*rl;
	char	*pr;
	t_parsed	*list;

	(void)ac;
	(void)av;
	rl = NULL;
	pr = prompt(envp);
	while (!ft_strnstr(rl, "exit", ft_strlen(rl)))// voir comment faire avec exceve pour "exit"
	{
		free(rl);
		rl = readline(pr);
		list = parse(envp, rl);//voir qu'est ce que je dois renvoyer (on peut changer en char *** ou n'importe)
		if (!list)
			break ;
		//show_arr(hist);
		//process(list);
		free(pr);
		pr = prompt(envp);
	}
	//ft_free_t_parsed(list, arr_size(list));
	free(pr);
	free(rl);
	return (0);
}

//on vas reorganiser tkt pas mdr
