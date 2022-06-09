/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:23:14 by krioja            #+#    #+#             */
/*   Updated: 2022/06/09 13:25:19 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int	populate_redir(t_ad *ad, const char *l)
static int	add_pa_redir(t_ad *ad, const char *l)
{
	int	ret;

	ret = 0;
	while (*(l + ret) == '>' || *(l + ret) == '<')
	{
		if (!ad->pa->redir)
			ad->pa->redir = redir_lstnew(ad->pa->redir);
		else
			redir_lstadd_next(&ad->pa->redir, redir_lstnew(ad->pa->redir));
		ad->pa->redir->op = ft_strtrim(
				ft_substr(l + ret, 0, ft_strlen_op(ad, l + ret)), " ");
		if (ad->pa->redir->op == NULL)
			my_exit(ad, write(2, "Error: Malloc (ad->pa->redir->op)\n", 30));
		ret += ft_strlen_op(ad, l + ret);
		ad->pa->redir->file = ft_strtrim(
				ft_substr(l + ret, 0, ft_strlen_sp(l + ret, 0)), " ");
		if (ad->pa->redir->file == NULL)
			my_exit(ad, write(2, "Error: Malloc (ad->pa->redir->file)\n", 32));
		if (!ad->pa->redir->file[0])
			my_exit(ad, write(2, "Error: Redir file not specified\n", 32));
		ret += ft_strlen_sp(l + ret, 0);
/*
		redir_lst_fst_or_lst(&ad->pa->redir, 0);
		while (ad->pa->redir)
		{
			ft_printf("-ad.pa.redir.op=|%s|\n", ad->pa->redir->op);
			ft_printf("ad.pa.redir.file=|%s|\n", ad->pa->redir->file);
			if (ad->pa->redir->next)
				ad->pa->redir = ad->pa->redir->next;
			else
				break;
		}
*/
	}
	return (ret);
}
/* to put before return (0) to check all redir structs
	while (ad->pa->redir)
	{
		ft_printf("ad.redir.op=|%s|\n", ad->pa->redir->op);
		ft_printf("ad.redir.file=|%s|\n", ad->pa->redir->file);
		ad->pa->redir = ad->pa->redir->next;
	}
*/

static int	populate_pa2(t_ad *ad, const char *l)
{
	int	n;
	int	ret;

	ft_printf(":O l=|%s|\n",l);
	n = 0;
	ret = 0;
/*	
	if (!ad->pa)
		ad->pa = pa_lstnew(ad->pa);
	else
		pa_lstadd_next(&ad->pa, pa_lstnew(ad->pa));
*/
	ret += add_pa_redir(ad, l + ret);
	ad->pa->cmd = ft_strtrim(ft_substr(l + ret, 0, ft_strlen_sp(l + ret, 0)), " ");
	if (!ad->pa->cmd || ad->pa->cmd[0] == '\0')
	{
		ft_printf("heyy\n");
		my_exit(ad, write(2, "Error: ad->pa->cmd is NULL\n", 27));
	}
	ad->pa->args = malloc(sizeof(char *) * (ft_count_args(l) + 1));
//	ft_printf("args=%d\n", ft_count_args(l));
	while (*(l + ret) != '|' && *(l + ret))
	{
//			ret += ft_strlen_op(ad, l + ret);
//			ret += ft_strlen_sp(l + ret, 0);
		ad->pa->args[n] = ft_strtrim(ft_substr(l + ret, 0,
					ft_strlen_sp(l + ret, 0)), " ");
		if (ad->pa->args[n] == NULL)
			my_exit(ad, write(2, "Error: ad->pa->args is NULL\n", 28));
//		ft_printf(":) arg[%d]=|%s|\n", n, ad->pa->args[n]);
		ret += ft_strlen_sp(l + ret, 0);
//		l += ft_strlen_sp(l, 0);
		++n;
		ret += add_pa_redir(ad, l + ret);
		ft_printf(":S l=|%s|\n",l + ret);
	}
//	ft_printf("n=%d\n", n);
//	ft_printf(":D l=|%s|, ret=%d\n",l + ret, ret);
	ad->pa->args[n] = NULL;
	return (ret);
}

/*
	static int	add_redir(t_ad *ad, const char *l)
{
	int	ret;

	ret = 0;
	ret += ft_strlen_op(ad, l);	
	ret += ft_strlen_sp(l + ret, 0);
//	if (!ad->pa)
//		ad->pa = pa_lstnew(NULL);
	if (!ad->pa->redir)
		ad->pa->redir = redir_lstnew(ad->pa->redir);
	else
		redir_lstadd_next(&ad->pa->redir, redir_lstnew(ad->pa->redir));
	ad->pa->redir = ad->redir;
	ft_printf(":) PA redir op=|%s|\n", ad->pa->redir->op);
	ft_printf(":) PA redir file=|%s|\n", ad->pa->redir->file);
	ad->redir = ad->redir->next;
	ft_printf(":D l=|%s|, ret=%d\n",l, ret);
	return (ret);
}*/

static int	populate_pa(t_ad *ad, const char *l)
{
	int	n;

	n = 0;
	ad->pa = pa_lstnew(NULL);
	while (*l)
	{
//		if (*l == '>' || *l == '<')
//			l += add_pa_redir(ad, l);
		if (*l != '|')
		{
			l += populate_pa2(ad, l);
			ft_printf("l = |%s|\n", l);
		}
//		else if (*l == '|')
		else
		{
			l += ft_strlen_sp(l, 0) + 1;
			if (*l == '\0' || *l == '|' || *l == '\0')
				my_exit(ad, write(2, "Error: pipe to nothing\n", 23));
//			ad->pa->redir->next = NULL;
			pa_lstadd_next(&ad->pa, pa_lstnew(ad->pa));
		}
//		else
//			l += populate_pa2(ad, l);
	}
/*
	if (ad->pa->prev != NULL)
	{
		ft_printf("YOOOO\n");
		pa_lst_fst_or_lst(&ad->pa, 0);
	}
*/
	n = 0;
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
//	ad->pa->redir->next = NULL;
	return (0);
}
/*
	to put before return (0) to check all redir structs
	pa_lst_fst_or_lst(&ad->pa, 0);
	n = 0;
	while (ad->pa)
	{
		ft_printf("ad.pa.cmd=|%s|\n", ad->pa->cmd);
		ft_printf("ad.pa.path=|%s|\n", ad->pa->path);
		while (ad->pa->args[n++])
			ft_printf("ad.pa.args[%d]=|%s|\n", n - 1, ad->pa->args[n - 1]);
		ad->pa = ad->pa->next;
		n = 0;
	}
*/


int	ms_split(t_ad *ad)
{
	int	i;

	i = 0;
	if (!ad->line)
		return (1);
//	if (populate_redir(ad, ft_strtrim(ad->line, " ")))
//		return (2);
	if (populate_pa(ad, ft_strtrim(ad->line, " ")))
		return (3);
	return (0);
}
