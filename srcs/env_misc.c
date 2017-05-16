/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 19:56:37 by jecarol           #+#    #+#             */
/*   Updated: 2017/05/16 22:23:33 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_print_env(t_env *env)
{
	while (env)
	{
		ft_putendl(env->var);
		env = env->next;
	}
}

int				ft_get_egal_pos(char *vartoadd)
{
	int			i;
	int			result;

	i = 0;
	result = 0;
	if (ft_strchr(vartoadd, '='))
	{
		while (vartoadd[i] != '=')
		{
			i++;
			result++;
		}
		return (result);
	}
	return (0);
}

void			ft_refresh_link(t_env **tmp, char *vartoadd)
{
	t_env		*tmp2;

	tmp2 = *tmp;
	ft_strdel(&tmp2->var);
	tmp2->var = ft_strdup(vartoadd);
}

void			ft_refresh_link_cd(t_env **tmp, char *vartoadd)
{
	t_env		*tmp2;
	int			i;

	i = 0;
	tmp2 = *tmp;
	while (tmp2)
	{
		if (!ft_strncmp(tmp2->var, vartoadd, 7))
		{
			ft_strdel(&tmp2->var);
			tmp2->var = ft_strdup(vartoadd);
			i = 1;
		}
		tmp2 = tmp2->next;
	}
	if (!i)
		ft_push_env(tmp, vartoadd);
}

void			ft_empty_env(t_env **env, int *i)
{
	ft_freelist(*env);
	*env = NULL;
	*i += 1;
}
