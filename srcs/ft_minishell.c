/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:22:14 by jecarol           #+#    #+#             */
/*   Updated: 2017/05/11 17:46:16 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**ft_getcmd(void)
{
	int			ret;
	char		buf[2];
	char		**cmd;
	char		*tmp;

	tmp = (char*)malloc(sizeof(char));
	ft_bzero(tmp, 1);
	ft_bzero(buf, 2);
	while ((ret = read(0, &buf, 1)) > 0 && !ft_strchr(buf, '\n'))
	{
		buf[ret] = '\0';
		if (buf[0] != '\t')
			tmp = ft_freejoin(tmp, buf);
	}
	if (tmp[0] == '\0')
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	cmd = ft_strsplit(tmp, ' ');
	ft_strdel(&tmp);
	return (cmd);
}

char			*find_cmd(t_data pvar, char *cmd)
{
	int			i;
	char		*tmp_path;

	i = 0;
	while (pvar.path && pvar.path[i])
	{
		tmp_path = ft_strjoin(pvar.path[i], cmd);
		if (!access(tmp_path, F_OK) && !ft_strstr(BUILTIN, cmd))
		{
			ft_strdel(&tmp_path);
			return (ft_strjoin(pvar.path[i], cmd));
		}
		ft_strdel(&tmp_path);
		i++;
	}
	return (NULL);
}

void			ft_execs(t_data *pvar, char **cmd, t_env **env)
{
	char		*path;

	ft_set_pvar(pvar, *env);
	if ((path = find_cmd(*pvar, cmd[0])))
		ft_exec_present(path, cmd, *env);
	else
		ft_exec_absent(path, cmd, pvar, env);
}

void			ft_prompt(void)
{
	char		cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_putstr(TURQUOISE);
	ft_putstr(cwd);
	ft_putstr("$>");
	ft_putstr(DEFAULT);
}

void			ft_minishell(t_env *env, t_data pvar)
{
	char		**cmd;
	char		*tmp;

	tmp = NULL;
	while (42)
	{
		ft_prompt();
		cmd = ft_getcmd();
		if (cmd && (tmp = ft_strtrim(cmd[0])))
		{
			ft_strdel(&tmp);
			ft_execs(&pvar, cmd, &env);
		}
		else
			ft_freetab(cmd);
	}
}
