/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:23:14 by krioja            #+#    #+#             */
/*   Updated: 2022/06/28 12:12:46 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	populate_redir(t_ad *ad, const char *l)
{
	int		ret;
	t_redir	*next;

	ret = 0;
	while (*(l + ret) == '>' || *(l + ret) == '<')
	{
		next = redir_lstnew(NULL);
		next->op = ft_strtrim_f(
				ft_substr(l + ret, 0, ft_strlen_op(ad, l + ret)), " ");
		if (next->op == NULL)
			my_exit(ad, write(2, "Error: Malloc (ad->pa->redir->op)\n", 30));
		ret += ft_strlen_op(ad, l + ret);
		next->file = ft_strtrim_f(
				ft_substr(l + ret, 0, ft_strlen_sp(l + ret, 0)), " ");
		if (next->file == NULL)
			my_exit(ad, write(2, "Error: Malloc (ad->pa->redir->file)\n", 32));
		if (!next->file[0])
			my_exit(ad, write(2, "Error: Redir file not specified\n", 32));
		ret += ft_strlen_sp(l + ret, 0);
		redir_lstadd_next(&ad->pa->redir, next);
	}
	return (ret);
}

static int	populate_pa(t_ad *ad, char *l)
{
	int	n;
	int	ret;

	n = 0;
	ret = 0;
	ret += populate_redir(ad, l + ret);
	ad->pa->cmd = ft_strtrim_f(ft_substr(l + ret, 0,
				ft_strlen_sp(l + ret, 0)), " ");
	if (is_builtins(ad))
		ad->pa->is_blt = 1;
	if (!ad->pa->cmd || ad->pa->cmd[0] == '\0')
		my_exit(ad, write(2, "Error: ad->pa->cmd is NULL\n", 27));
	ad->pa->args = malloc(sizeof(char *) * (ft_count_args(l) + 1));
	while (*(l + ret) != '|' && *(l + ret))
	{
		while (*(l + ret) == ' ')
			ret++;
		if (*(l + ret) == '\'')
		{
			ad->pa->args[n] = ft_strtrim_f(ft_substr(l + ret, 0,pos_n_char(l + ret, 2, '\'')), " ");
			ret += pos_n_char(l + ret, 2, '\'');
		}
		else if (*(l + ret) == '"')
		{
			ad->pa->args[n] = ft_strtrim_f(ft_substr(l + ret, 0,pos_n_char(l + ret, 2, '"')), "\"");
			ret += pos_n_char(l + ret, 2, '"');
		}
		else
		{
			ad->pa->args[n] = ft_strtrim_f(ft_substr(l + ret, 0, ft_strlen_sp(l + ret, 0)), " ");
			ret += ft_strlen_sp(l + ret, 0);
		}
		if (ad->pa->args[n] == NULL)
			my_exit(ad, write(2, "Error: ad->pa->args is NULL\n", 28));
		++n;
		ret += populate_redir(ad, l + ret);
	}
	ad->pa->args[n] = NULL;
	return (ret);
}

static int	parse_line(t_ad *ad, char *l)
{
	char	*tmp;

	ad->pa = pa_lstnew(NULL);
	ad->pa_head = ad->pa;
	tmp = l;
	while (*l)
	{
		if (*l != '|')
			l += populate_pa(ad, l);
		else
		{
			if (!ad->pa->cmd || ad->pa->cmd[0] == '\0')
				return (1);
			++l;
			while (ft_isspace(*l) && *l)
				++l;
			pa_lstadd_next(&ad->pa, pa_lstnew(ad->pa));
		}
	}
	if (!ad->pa->cmd || ad->pa->cmd[0] == '\0')
		return (1);
	free(tmp);
	check_dollar(ad);
	return (0);
}
/*
	to put before return (0) to check all redir structs
	int	n = 0;
 	pa_lst_fst_or_lst(&ad->pa, 0);
	while (ad->pa)
	{
		ft_printf("--ad.pa.cmd=|%s|\n", ad->pa->cmd);
		ft_printf("ad.pa.path=|%s|\n", ad->pa->path);
		while (ad->pa->args[n])
		{
			ft_printf("ad.pa.args[%d]=|%s|\n", n, ad->pa->args[n]);
			++n;
		}
		redir_lst_fst_or_lst(&ad->pa->redir, 0);
		while (ad->pa->redir)
		{
			ft_printf("ad.pa.redir.op=|%s|\n", ad->pa->redir->op);
			ft_printf("ad.pa.redir.file=|%s|\n", ad->pa->redir->file);
			if (ad->pa->redir->next)
				ad->pa->redir = ad->pa->redir->next;
			else
				break;
		}
		ad->pa = ad->pa->next;
		n = 0;
	}
	pa_lst_fst_or_lst(&ad->pa, 0);
*/

int	ms_split(t_ad *ad)
{
	char	*tmp;

	if (!ad->line)
		return (1);
	if (!check_quote(ad->line, '\'') || !check_quote(ad->line, '"'))
		return (2);
	tmp = ft_strtrim(ad->line, " ");
	if (parse_line(ad, tmp))
	{
		free(tmp);
		return (2);
	}
	return (0);
}
