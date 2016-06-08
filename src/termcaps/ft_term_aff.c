/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_aff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 16:20:07 by lscariot          #+#    #+#             */
/*   Updated: 2016/05/17 15:41:25 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	ft_aff_line(t_gen *gen)
{
	int i;

	i = 0;
	while (gen->tcaps->line[i])
	{
		if (((i >= gen->tcaps->cut1 && i <= gen->tcaps->cut2)
				|| (i <= gen->tcaps->cut1 && i >= gen->tcaps->cut2))
				&& (gen->tcaps->cut1 != -1 || gen->tcaps->cut2 != -1))
		{
			ft_putstr("\e[7m");
			ft_putchar(gen->tcaps->line[i++]);
			ft_putstr("\e[0m");
		}
		else
			ft_putchar(gen->tcaps->line[i++]);
	}
}
