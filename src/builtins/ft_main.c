/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 11:38:01 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/01 23:50:27 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		ft_builtins_exec(t_gen *gen, char **tab, int i)
{
	static t_builtins	*buil[11] = {
		&ft_exit,
		&ft_cd,
		&ft_echo,
		&ft_env,
		&ft_setenv,
		&ft_unsetenv,
		&ft_clear,
		&ft_history,
		&ft_alias,
		&ft_source,
		&ft_setalias
	};

	return ((buil[i])(gen, tab));
}

int		ft_builtins_while(t_gen *gen, char **buil, char **tab)
{
	int		i;

	i = 0;
	while (buil[i])
	{
		if (ft_strcmp(tab[0], buil[i]) == 0)
		{
			return (ft_builtins_exec(gen, tab, i));
			break ;
		}
		i++;
	}
	return (1);
}

int		ft_builtins(t_gen *gen, char **tab)
{
	static char	*buil[12] = {NULL};

	if (buil[0] == NULL)
	{
		buil[0] = ft_strdup("exit");
		buil[1] = ft_strdup("cd");
		buil[2] = ft_strdup("echo");
		buil[3] = ft_strdup("env");
		buil[4] = ft_strdup("setenv");
		buil[5] = ft_strdup("unsetenv");
		buil[6] = ft_strdup("clear");
		buil[7] = ft_strdup("history");
		buil[8] = ft_strdup("alias");
		buil[9] = ft_strdup("source");
		buil[10] = ft_strdup("setalias");
		buil[11] = NULL;
	}
	return (ft_builtins_while(gen, buil, tab));
}
