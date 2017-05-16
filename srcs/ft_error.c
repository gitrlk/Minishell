/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlkcmptr <rlkcmptr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 03:33:36 by rlkcmptr          #+#    #+#             */
/*   Updated: 2017/05/10 18:31:57 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				ft_relativ_error(int err, char *cmd)
{
	if (err == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else if (err == 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": no such file or directory", 2);
	}
	else if (err == 1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": is a directory", 2);
	}
	else if (err == 2)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": permission denied", 2);
	}
	else if (err == -42)
		ft_putendl_fd("Unknown error", 2);
}

void				ft_error(int err, char *cmd, char *arg)
{
	if (err == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else if (err == 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": no such file or directory: ", 2);
		ft_putendl_fd(arg, 2);
	}
	else if (err == 1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": not a directory: ", 2);
		ft_putendl_fd(arg, 2);
	}
	else if (err == 2)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": permission denied: ", 2);
		ft_putendl_fd(arg, 2);
	}
	else if (err == -42)
		ft_putendl_fd("Unknown error", 2);
}

void				ft_cd_errors(char **cmd)
{
	struct stat		stats;

	if (access(cmd[1], F_OK))
		ft_error(0, cmd[0], cmd[1]);
	else
	{
		if (!stat(cmd[1], &stats))
		{
			if (!(S_IFDIR >> 9 == (stats.st_mode >> 9)))
				ft_error(1, cmd[0], cmd[1]);
			else if (!(stats.st_mode & S_IXUSR))
				ft_error(2, cmd[0], cmd[1]);
		}
		else
			ft_error(-42, NULL, NULL);
	}
}
