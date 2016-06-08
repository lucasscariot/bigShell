/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setalias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 11:41:31 by hfrely            #+#    #+#             */
/*   Updated: 2016/05/15 20:21:30 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		ft_alias_null(t_gen *gen, char *str)
{
	char	**split;

	if (gen->alias == NULL)
	{
		split = ft_strsplit(str, '=');
		if (ft_tablen(split) != 2)
			return (1);
		gen->alias = ft_create_alias(gen->alias, split[0], split[1]);
		return (1);
	}
	return (0);
}

int		check_alias_un(t_gen *gen, char **split)
{
	while (gen->alias->prev)
		gen->alias = gen->alias->prev;
	if (ft_tablen(split) != 2)
	{
		ft_freetab(split);
		return (1);
	}
	return (0);
}

int		check_alias(t_gen *gen, char *str)
{
	char	**split;

	if (ft_alias_null(gen, str))
		return (0);
	split = ft_strsplit(str, '=');
	if (check_alias_un(gen, split))
		return (0);
	while (gen->alias)
	{
		if (ft_strcmp(gen->alias->cmd, split[0]) == 0)
		{
			free(gen->alias->replace);
			gen->alias->replace = ft_strdup(split[1]);
			ft_freetab(split);
			return (0);
		}
		if (gen->alias->next == NULL)
			break ;
		gen->alias = gen->alias->next;
	}
	gen->alias = ft_create_alias(gen->alias, split[0], split[1]);
	ft_freetab(split);
	return (0);
}

int		ft_setalias(t_gen *gen, char **tab)
{
	int		ac;

	ac = ft_tablen(tab);
	if (ac == 2)
		check_alias(gen, tab[1]);
	return (0);
}
