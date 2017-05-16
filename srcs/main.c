/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:04:58 by jecarol           #+#    #+#             */
/*   Updated: 2017/05/10 18:31:41 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_init_all_paths(char **paths)
{
	int			i;
	char		*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
}

void			ft_set_pvar_assist(t_data *pvar, t_env *env)
{
	char		*tmp;

	if (!ft_strncmp("PATH=", env->var, 5))
	{
		ft_freetab(pvar->path);
		tmp = ft_strdup(env->var + 5);
		pvar->path = ft_strsplit(tmp, ':');
		free(tmp);
		ft_init_all_paths(pvar->path);
	}
	else if (!ft_strncmp("HOME=", env->var, 5))
	{
		if (pvar->home)
			ft_strdel(&pvar->home);
		pvar->home = ft_strdup(env->var + 5);
	}
	else if (!ft_strncmp("OLDPWD=", env->var, 7))
	{
		if (pvar->oldpwd)
			ft_strdel(&pvar->oldpwd);
		pvar->oldpwd = ft_strdup(env->var + 7);
	}
}

void			ft_set_pvar(t_data *pvar, t_env *env)
{
	t_env		*tmp;

	tmp = env;
	if (!tmp)
	{
		ft_freetab(pvar->path);
		ft_strdel(&pvar->oldpwd);
		ft_strdel(&pvar->home);
		pvar->path = NULL;
	}
	while (tmp)
	{
		ft_set_pvar_assist(pvar, tmp);
		tmp = tmp->next;
	}
}

int				main(int ac, char **av, char **envp)
{
	t_env		*env;
	int			i;
	t_data		pvar;

	(void)ac;
	(void)av;
	env = NULL;
	i = 0;
	ft_memset(&pvar, 0, sizeof(pvar));
	while (envp[i])
		ft_push_env(&env, envp[i++]);
	ft_minishell(env, pvar);
	return (0);
}
