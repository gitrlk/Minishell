/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 14:17:20 by jecarol           #+#    #+#             */
/*   Updated: 2017/05/10 18:20:04 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUILTIN "exit echo cd env setenv unsetenv"

# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <signal.h>

typedef struct		s_data
{
	char			**path;
	char			*home;
	char			*oldpwd;
}					t_data;

typedef struct		s_env
{
	char			*var;
	struct s_env	*next;
}					t_env;

typedef struct		s_vals
{
	int				i;
	int				size;
}					t_vals;

void				ft_exec_absent(char *path, char **cmd,
					t_data *pvar, t_env **env);
void				ft_exec_present(char *path, char **cmd, t_env *env);
void				ft_freetab(char **tab);
void				ft_cd(char **cmd, t_data *pvar, t_env *env);
void				ft_push_env(t_env **lst, char *var);
t_env				*ft_add_env(char *var);
void				ft_exit(char *path, char **cmd, t_data *pvar, t_env *lst);
void				ft_echo(char **cmd);
void				ft_minishell(t_env *env, t_data pvar);
void				ft_error(int err, char *cmd, char *arg);
void				ft_print_env(t_env *env);
void				ft_cd_errors(char **cmd);
void				ft_relativ_error(int err, char *cmd);
void				ft_env(t_env *env, char **cmd, t_data *pvar);
char				*find_cmd(t_data pvar, char *cmd);
void				ft_freetab(char **tab);
void				ft_freelist(t_env *lst);
void				ft_set_pvar(t_data *pvar, t_env *env);
void				ft_add_env_var(t_env *env, char *vartoadd);
void				ft_execs(t_data *pvar, char **cmd, t_env **env);
int					ft_get_egal_pos(char *vartoadd);
char				**ft_fill_envp(t_env *env);
void				ft_refresh_link(t_env **tmp, char *vartoadd);
void				ft_empty_env(t_env **env, int *i);
void				ft_env_with_var(t_env **env, char *vartoadd);
void				ft_setenv(t_env **env, char **cmd);
void				ft_unsetenv(t_env **env, char **cmd, t_data *pvar);
void				ft_refresh_link_cd(t_env **tmp, char *vartoadd);

#endif
