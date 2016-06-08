/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 12:34:19 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/08 14:28:27 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		ft_cd_last(t_gen *gen)
{
	char *tmp;

	if ((tmp = ft_getenv(gen, "OLDPWD=")) == NULL)
	{
		ft_putstr("cd: OLDPWD is not set.\n");
		return (1);
	}
	ft_modenv(gen, "OLDPWD=", getcwd(NULL, 100));
	if (chdir(tmp) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(tmp);
		return (1);
	}
	ft_modenv(gen, "PWD=", getcwd(NULL, 100));
	return (0);
}

int		ft_cd_un(t_gen *gen)
{
	char	*tmp;

	if ((tmp = ft_getenv(gen, "HOME=")) == NULL)
		return (1);
	ft_modenv(gen, "OLDPWD=", getcwd(NULL, 100));
	if (chdir(tmp) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(tmp);
		return (1);
	}
	ft_modenv(gen, "PWD=", getcwd(NULL, 100));
	free(tmp);
	return (0);
}

int		ft_cd_deux(char *str, t_gen *gen)
{
	ft_modenv(gen, "OLDPWD=", getcwd(NULL, 100));
	if (chdir(str) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(str);
		return (1);
	}
	ft_modenv(gen, "PWD=", getcwd(NULL, 100));
	return (0);
}

int		ft_cd_trois(t_gen *gen, char *opt, char *dir)
{
	(void)gen;
	(void)opt;
	(void)dir;
	return (0);
}

int		ft_cd(t_gen *gen, char **tab)
{
	int		ac;

	ac = ft_tablen(tab);
	if (ac == 1)
		return (ft_cd_un(gen));
	else if (ac == 2 && tab[1][0] == '-')
		return (ft_cd_last(gen));
	else if (ac == 2)
		return (ft_cd_deux(tab[1], gen));
	else if (ac == 3)
		return (ft_cd_trois(gen, tab[1], tab[2]));
	return (1);
}
