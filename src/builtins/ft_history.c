/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 19:47:40 by lscariot          #+#    #+#             */
/*   Updated: 2016/05/15 20:20:41 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		ft_history(t_gen *gen, char **tab)
{
	t_caps	*tmp;

	if (!gen->tcaps)
		return (1);
	(void)tab;
	tmp = gen->tcaps;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		ft_putendl(tmp->line);
		tmp = tmp->next;
	}
	return (0);
}
