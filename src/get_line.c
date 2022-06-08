/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:11:14 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/04 17:34:17 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_line(t_ad *ad)
{
	struct termios	saved;
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &saved);
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
	ad->line = readline("adsh> ");
	if (ad->line)
		add_history(ad->line);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
	if (!ad->line)
		return (0);
	return (1);
}

// TODO changer var ad->line par ad->pa->cmd
void	check_line(t_ad *ad)
{
	if (!ft_strncmp(MS_ECHO, ad->line, ft_strlen(MS_ECHO)))
		ft_echo(ad);
	else if (!ft_strncmp(MS_CD, ad->line, ft_strlen(MS_CD)))
		ft_cd(ad);
	else if (!ft_strncmp(MS_PWD, ad->line, ft_strlen(MS_PWD)))
		ft_pwd(ad);
	else if (!ft_strncmp(MS_EXPORT, ad->line, ft_strlen(MS_EXPORT)))
		ft_export(ad);
	else if (!ft_strncmp(MS_UNSET, ad->line, ft_strlen(MS_UNSET)))
		ft_unset(ad);
	else if (!ft_strncmp(MS_ENV, ad->line, ft_strlen(MS_ENV)))
		ft_env(ad);
	else if (!ft_strncmp(MS_EXIT, ad->line, ft_strlen(MS_EXIT)))
	{
		// TODO do function exit and free
		ft_printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else
		check_path(ad);
	// 	write(2, "adsh: command not found\n", 25);
}
