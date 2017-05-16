/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:23:42 by jecarol           #+#    #+#             */
/*   Updated: 2017/05/10 20:28:30 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_cd_minus(t_data *pvar, t_env *env, char *curr_path)
{
	char					*tmp;

	if (env)
	{
		tmp = ft_strjoin("OLDPWD=", curr_path);
		ft_refresh_link_cd(&env, tmp);
		ft_strdel(&tmp);
	}
	if (pvar->oldpwd && !access(pvar->oldpwd, F_OK))
	{
		ft_putendl(pvar->oldpwd);
		chdir(pvar->oldpwd);
	}
	else
		ft_putendl_fd("cd: OLDPWD not set", 2);
}

void		ft_cd_home_not_valid(char *wrongpath)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(wrongpath, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void		ft_cd_home(char *tmp, t_env *env, t_data *pvar, char *curr_path)
{
	if (env)
	{
		tmp = ft_strjoin("OLDPWD=", curr_path);
		ft_refresh_link_cd(&env, tmp);
		ft_strdel(&tmp);
	}
	if (pvar->home)
	{
		if (!access(pvar->home, F_OK))
			chdir(pvar->home);
		else
			ft_cd_home_not_valid(pvar->home);
	}
	else
	{
		if (pvar->home)
		{
			ft_putstr_fd("cd : ", 2);
			ft_putstr_fd(pvar->home, 2);
			ft_putendl_fd(": No such file or directory", 2);
		}
		else
			ft_putendl_fd("cd: HOME not set", 2);
	}
}

void		ft_cd(char **cmd, t_data *pvar, t_env *env)
{
	char					curr_path[1024];
	char					*tmp;

	tmp = NULL;
	getcwd(curr_path, sizeof(curr_path));
	if (!cmd[1])
		ft_cd_home(tmp, env, pvar, curr_path);
	else if (!ft_strcmp(cmd[1], "-"))
		ft_cd_minus(pvar, env, curr_path);
	else if (chdir(cmd[1]))
		ft_cd_errors(cmd);
	else
	{
		if (env)
		{
			tmp = ft_strjoin("OLDPWD=", curr_path);
			ft_refresh_link_cd(&env, tmp);
			ft_strdel(&tmp);
		}
	}
}
