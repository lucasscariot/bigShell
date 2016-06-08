/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_fnt2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 14:58:41 by lscariot          #+#    #+#             */
/*   Updated: 2016/06/08 14:46:45 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	ft_delstrsub(t_gen *gen)
{
	int		i;

	if (gen->tcaps->cut1 > gen->tcaps->cut2)
	{
		i = gen->tcaps->cut1;
		gen->tcaps->cut1 = gen->tcaps->cut2;
		gen->tcaps->cut2 = i;
	}
	i = gen->tcaps->cut2 + 1;
	gen->copy = ft_strsub(gen->tcaps->line, gen->tcaps->cut1,
			i - gen->tcaps->cut1);
	gen->tcaps->cursor = i;
	if (gen->tcaps->cut1 == gen->tcaps->cut2)
		exec_del(gen, NULL);
	else
	{
		while (gen->tcaps->cut1 < i)
		{
			exec_del(gen, NULL);
			i--;
		}
	}
}

void	exec_ctrl_l(t_gen *gen, char *buf)
{
	(void)buf;
	ft_putstr("\033[2J\033[1;1H");
	ft_refresh(gen);
}

void	exec_ctrl_d(t_gen *gen, char *buf)
{
	if (gen->tcaps->len <= 0)
		exit(1);
	else if (gen->tcaps->cursor == gen->tcaps->len)
		return ;
	else if (gen->tcaps->len > gen->tcaps->cursor)
	{
		gen->tcaps->cursor++;
		exec_del(gen, buf);
	}
}
