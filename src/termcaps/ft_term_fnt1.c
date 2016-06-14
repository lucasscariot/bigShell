/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_fnt1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <lscariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 11:13:36 by lscariot          #+#    #+#             */
/*   Updated: 2016/06/14 13:42:02 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	exec_x_alt(t_gen *gen, char *buf)
{
	(void)buf;
	if ((gen->tcaps->cut1 == -1 && gen->tcaps->cut2 == -1)
			|| (gen->tcaps->cut1 == 0 && gen->tcaps->cut2 == 0)
			|| (gen->tcaps->cut1 == gen->tcaps->len
				&& gen->tcaps->cut2 == gen->tcaps->len)
			|| (gen->tcaps->cut1 == 0 && gen->tcaps->cut2 == gen->tcaps->len))
		return ;
	ft_delstrsub(gen);
	gen->tcaps->cut1 = -1;
	gen->tcaps->cut2 = -1;
	ft_refresh(gen);
}

void	exec_v_alt(t_gen *gen, char *buf)
{
	(void)buf;
	if (gen->copy)
		exec_write(gen, gen->copy);
}

void	ft_refresh(t_gen *gen)
{
	int	tmp;

	exec_clean(gen);
	ft_prompt(gen);
	ft_aff_line(gen);
	tmp = gen->tcaps->len;
	while (tmp > gen->tcaps->cursor)
	{
		ft_putstr_fd(tgetstr("le", NULL), gen->fd);
		tmp--;
	}
}

void	ft_select_left(t_gen *gen)
{
	if (gen->tcaps->cut1 == gen->tcaps->cut2 && gen->tcaps->cut1 != -1)
		exec_z_alt(gen, NULL);
	if ((gen->tcaps->cut1 != -1 || gen->tcaps->cut2 != -1)
			&& gen->tcaps->cut2 > gen->tcaps->cursor)
	{
		if (gen->tcaps->cut1 >= gen->tcaps->cut2)
			gen->tcaps->cut1--;
		gen->tcaps->cut2--;
	}
}

void	ft_select_right(t_gen *gen)
{
	if ((gen->tcaps->cut1 != -1 || gen->tcaps->cut2 != -1)
			&& gen->tcaps->cut2 < gen->tcaps->cursor)
	{
		if (gen->tcaps->cut1 > gen->tcaps->cut2)
			gen->tcaps->cut1++;
		gen->tcaps->cut2++;
	}
}
