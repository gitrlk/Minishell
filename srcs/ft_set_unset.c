/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 15:21:12 by jecarol           #+#    #+#             */
/*   Updated: 2017/05/10 18:31:53 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_setenv_assist(t_env *tmp, int egal, char *var, int *checker)
{
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, var, egal) && tmp->var[egal] == '=')
		{
			ft_refresh_link(&tmp, var);
			*checker = 1;
			break ;
		}
		tmp = tmp->next;
	}
}

void		ft_setenv(t_env **env, char **cmd)
{
	t_env		*tmp;
	int			i;
	int			egal;
	int			checker;

	i = 1;
	while (cmd[i])
	{
		checker = 0;
		tmp = *env;
		egal = ft_get_egal_pos(cmd[i]);
		if (egal)
		{
			ft_setenv_assist(tmp, egal, cmd[i], &checker);
			if (!checker)
				ft_push_env(env, cmd[i]);
		}
		i++;
	}
}

void		ft_check_first_elem(t_env **env, char **cmd, t_vals *values,
			t_env *todel)
{
	if (*env && !ft_strncmp((*env)->var, cmd[values->i], values->size) &&
	(*env)->var[values->size] == '=')
	{
		todel = (*env);
		(*env) = (*env)->next;
		ft_strdel(&todel->var);
		free(todel);
	}
}

void		ft_check_path_home_oldpwd(t_data *pvar, char *arg)
{
	if (!ft_strcmp(arg, "PATH"))
		if (pvar->path)
		{
			ft_freetab(pvar->path);
			pvar->path = NULL;
		}
	if (!ft_strcmp(arg, "HOME"))
		if (pvar->home)
		{
			ft_strdel(&pvar->home);
			pvar->home = NULL;
		}
	if (!ft_strcmp(arg, "OLDPWD"))
		if (pvar->oldpwd)
		{
			ft_strdel(&pvar->oldpwd);
			pvar->oldpwd = NULL;
		}
}

void		ft_unsetenv(t_env **env, char **cmd, t_data *pvar)
{
	t_env		*tmp;
	t_env		*todel;
	t_vals		values;

	values.i = 1;
	values.size = 0;
	if (!cmd[values.i])
		return ;
	while (cmd[values.i][values.size])
		values.size++;
	tmp = *env;
	while (tmp)
	{
		todel = tmp->next;
		if (tmp->next && !ft_strncmp(tmp->next->var, cmd[values.i], values.size)
		&& tmp->next->var[values.size] == '=')
		{
			tmp->next = tmp->next->next;
			ft_strdel(&todel->var);
			free(todel);
		}
		tmp = tmp->next;
	}
	ft_check_first_elem(env, cmd, &values, todel);
	ft_check_path_home_oldpwd(pvar, cmd[values.i]);
}
