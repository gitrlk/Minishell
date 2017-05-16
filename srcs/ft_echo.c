/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlkcmptr <rlkcmptr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 03:29:05 by rlkcmptr          #+#    #+#             */
/*   Updated: 2017/04/25 20:26:19 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_echo(char **cmd)
{
	int			i;

	if (!cmd[1])
		ft_putchar('\n');
	if (cmd[1])
	{
		i = (ft_strcmp(cmd[1], "-n") == 0 ? 2 : 1);
		while (cmd[i])
		{
			ft_putstr(cmd[i]);
			if (cmd[i + 1])
				write(1, " ", 1);
			i++;
		}
		if (ft_strcmp(cmd[1], "-n") != 0)
			write(1, "\n", 1);
	}
}
