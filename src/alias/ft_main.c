/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 21:54:53 by hfrely            #+#    #+#             */
/*   Updated: 2016/05/17 12:29:01 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	**ft_change_alias_un(char **new, char **tab, char **split)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (tab[i])
	{
		if (i == 0)
		{
			while (split[j])
			{
				new[j] = ft_strdup(split[j]);
				j++;
			}
			i++;
			continue ;
		}
		new[j] = ft_strdup(tab[i]);
		j++;
		i++;
	}
	new[j] = NULL;
	return (new);
}

char	**ft_change_alias(t_gen *gen, char **tab)
{
	char	**new;
	char	**split;

	split = ft_strsplit(gen->alias->replace, ' ');
	if (split[0] == NULL)
		return (tab);
	new = (char **)malloc(sizeof(char *) * (ft_tablen(tab)
				+ ft_tablen(split) + 1));
	new = ft_change_alias_un(new, tab, split);
	if (split)
		ft_freetab(split);
	if (new)
		ft_freetab(tab);
	else
		return (tab);
	return (new);
}

char	**ft_alias_cmp(t_gen *gen, char **tab)
{
	while (gen->alias->prev)
		gen->alias = gen->alias->prev;
	while (gen->alias)
	{
		if (ft_strcmp(gen->alias->cmd, tab[0]) == 0)
			return (ft_change_alias(gen, tab));
		if (gen->alias->next == NULL)
			break ;
		gen->alias = gen->alias->next;
	}
	return (tab);
}

char	**ft_check_alias(t_gen *gen, char **tab)
{
	if (gen->alias == NULL)
		return (tab);
	return (ft_alias_cmp(gen, tab));
}
