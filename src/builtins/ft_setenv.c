/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 14:18:49 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/08 14:33:36 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	check_env(t_gen *gen, char *str)
{
	char	**split;
	char	*tmp;

	while (gen->env->prev)
		gen->env = gen->env->prev;
	split = ft_strsplit(str, '=');
	tmp = ft_strjoin(split[0], "=");
	while (gen->env)
	{
		if (ft_strcmp(gen->env->name, tmp) == 0)
		{
			free(gen->env->content);
			gen->env->content = ft_strdup(split[1]);
			free(tmp);
			ft_freetab(split);
			return ;
		}
		if (gen->env->next == NULL)
			break ;
		gen->env = gen->env->next;
	}
	free(tmp);
	gen->env = ft_env_list(gen->env, split[0], split[1]);
	ft_freetab(split);
}

void	check_env_null(t_gen *gen, char *str)
{
	char	**split;
	char	*tmp;

	split = ft_strsplit(str, '=');
	tmp = ft_strjoin(split[0], "=");
	gen->env = ft_env_list(gen->env, split[0], split[1]);
}

int		ft_setenv(t_gen *gen, char **tab)
{
	int		ac;
	int		i;

	i = 1;
	ac = ft_tablen(tab);
	if (ac >= 2)
	{
		while (tab[i])
		{
			if (gen->env == NULL)
			{
				check_env_null(gen, tab[i]);
				return (0);
			}
			check_env(gen, tab[i]);
			i++;
		}
		return (0);
	}
	return (1);
}
