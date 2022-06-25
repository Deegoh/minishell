/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:30:56 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/24 13:46:45 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

size_t	ft_strlen_c(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_strtolower(char *str)
{
	int	i;

	if (str)
	{
		i = ft_strlen(str);
		while (i--)
			str[i] = ft_tolower(str[i]);
	}
	else
		str = "";
	return (str);
}

void	custom_err(t_ad *ad, int arg, char *str)
{
	write(2, SHELL_NAME, ft_strlen(SHELL_NAME));
	if (arg != 0)
	{
		write(2, ": ", 2);
		write(2, ad->pa->cmd, ft_strlen(ad->pa->cmd));
	}
	write(2, ": ", 2);
	write(2, ad->pa->args[arg], ft_strlen(ad->pa->args[arg]));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}
