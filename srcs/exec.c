/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:18:15 by jecarol           #+#    #+#             */
/*   Updated: 2017/05/16 22:25:18 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_son_exec(char **cmd)
{
	struct stat		stats;

	if (stat(cmd[0], &stats) == 0)
	{
		if (S_IFDIR >> 9 == (stats.st_mode >> 9))
			ft_relativ_error(1, cmd[0]);
		else if (!(stats.st_mode & S_IXUSR))
			ft_relativ_error(2, cmd[0]);
	}
	else
		ft_relativ_error(-42, NULL);
	exit(0);
}

void		ft_relativ_path(char **cmd, t_env *env)
{
	pid_t		pid;
	char		**newenvp;

	newenvp = ft_fill_envp(env);
	if (access(cmd[0], F_OK) == 0)
	{
		pid = fork();
		if (!pid)
		{
			if (execve(cmd[0], cmd, newenvp) == -1)
				ft_son_exec(cmd);
		}
		else if (pid > 0)
			wait(NULL);
	}
	else
		ft_relativ_error(0, cmd[0]);
	ft_freetab(newenvp);
}

void		ft_exec_present(char *path, char **cmd, t_env *env)
{
	pid_t		pid;
	char		**newenvp;

	newenvp = ft_fill_envp(env);
	pid = fork();
	if (!pid)
		execve(path, cmd, newenvp);
	else if (pid > 0)
		wait(NULL);
	ft_freetab(newenvp);
	ft_freetab(cmd);
	ft_strdel(&path);
}

void		ft_exec_absent(char *path, char **cmd, t_data *pvar, t_env **env)
{
	if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(cmd, pvar, *env);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(path, cmd, pvar, *env);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env(*env, cmd, pvar);
	else if (!ft_strcmp(cmd[0], "setenv"))
		ft_setenv(env, cmd);
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		ft_unsetenv(env, cmd, pvar);
	else if (cmd[0][0] == '/' || cmd[0][0] == '.')
		ft_relativ_path(cmd, *env);
	else
		ft_error(-1, cmd[0], NULL);
	ft_freetab(cmd);
	ft_strdel(&path);
}
