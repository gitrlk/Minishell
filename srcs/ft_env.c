/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlkcmptr <rlkcmptr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 03:23:59 by rlkcmptr          #+#    #+#             */
/*   Updated: 2017/05/16 22:24:45 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**copypasta(char **src, int i)
{
	int			size;
	int			j;
	char		**ret;

	size = 0;
	j = 0;
	while (src[size])
		size++;
	if (!(ret = (char **)malloc(sizeof(char *) * size)))
		return (NULL);
	while (src[i])
	{
		ret[j] = ft_strdup(src[i]);
		i++;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}

t_env			*ft_copy_list(t_env *env)
{
	t_env		*tmp;
	t_env		*head;
	t_env		*new;

	tmp = env;
	new = ft_memalloc(sizeof(t_env));
	head = new;
	new->var = ft_strdup(tmp->var);
	while (tmp->next)
	{
		new->next = ft_memalloc(sizeof(t_env));
		new->next->var = ft_strdup(tmp->next->var);
		new->next->next = NULL;
		new = new->next;
		tmp = tmp->next;
	}
	return (head);
}

void			ft_env_with_var(t_env **env, char *vartoadd)
{
	t_env		*tmp;
	int			egal;

	tmp = *env;
	egal = ft_get_egal_pos(vartoadd);
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, vartoadd, egal))
		{
			ft_refresh_link(&tmp, vartoadd);
			return ;
		}
		tmp = tmp->next;
	}
	ft_push_env(env, vartoadd);
}

void			ft_env(t_env *env, char **cmd, t_data *pvar)
{
	t_env		*new_env;
	char		**new_cmd;
	int			i;

	i = 1;
	new_env = (env ? ft_copy_list(env) : NULL);
	if (!cmd[i])
		ft_print_env(new_env);
	else
	{
		if (!ft_strcmp(cmd[i], "-i"))
			ft_empty_env(&new_env, &i);
		if (cmd[i] && cmd[i][0] != '=' && ft_strchr(cmd[i], '='))
			ft_env_with_var(&new_env, cmd[i++]);
		if (cmd[i])
		{
			new_cmd = copypasta(cmd, i);
			ft_execs(pvar, new_cmd, &new_env);
		}
		else
			ft_print_env(new_env);
	}
	if (new_env)
		ft_freelist(new_env);
}
