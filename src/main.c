/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:51:07 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/07/06 18:30:49 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// test
//   echo 12345 "67890 $? qwert $USER" $USER yuiop~ 'echo "lol" $USER' mdr
//output: 12345 67890 0 qwert tpinto-m tpinto-m yuiop~ echo "lol" $USER mdr
int	main(int ac, char **av, char **env)
{
	t_ad	ad;
	int		tmp;

	init(&ad, env);
	while (1)
	{
		handle_signal();
		if (!get_line(&ad))
			break ;
		tmp = ms_split(&ad);
		if (tmp == 1)
			break ;
		if (tmp == 2 || tmp == 3)
			continue ;
		if (ms_exec(&ad))
			break ;
		free_cmd(&ad);
	}
	free_all(&ad);
	(void)ac;
	(void)av;
	(void)env;
	return (EXIT_SUCCESS);
}
