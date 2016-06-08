/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 10:29:38 by hfrely            #+#    #+#             */
/*   Updated: 2016/05/15 20:17:14 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		aff_alias(t_gen *gen)
{
	if (gen->alias == NULL)
		return (0);
	while (gen->alias->prev)
		gen->alias = gen->alias->prev;
	while (gen->alias)
	{
		ft_putstr(gen->alias->cmd);
		ft_putchar('=');
		ft_putendl(gen->alias->replace);
		if (gen->alias->next == NULL)
			break ;
		gen->alias = gen->alias->next;
	}
	return (0);
}

int		ft_alias(t_gen *gen, char **tab)
{
	int		ac;

	ac = ft_tablen(tab);
	if (ac == 1)
		return (aff_alias(gen));
	return (1);
}
