/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlkcmptr <rlkcmptr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 03:26:20 by rlkcmptr          #+#    #+#             */
/*   Updated: 2017/05/10 18:40:42 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_freelist(t_env *lst)
{
	t_env		*tmp;

	tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		ft_strdel(&tmp->var);
		free(tmp);
	}
}

void			ft_freetab(char **tab)
{
	int			i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		ft_strdel((&tab[i]));
		i++;
	}
	ft_memdel((void **)&tab);
}

void			ft_exit(char *path, char **cmd, t_data *pvar, t_env *lst)
{
	int i;

	i = 0;
	(void)lst;
	ft_freetab(cmd);
	ft_freetab(pvar->path);
	ft_strdel(&pvar->oldpwd);
	ft_strdel(&pvar->home);
	ft_freelist(lst);
	ft_strdel(&path);
	ft_putendl("exit");
	exit(EXIT_SUCCESS);
}
