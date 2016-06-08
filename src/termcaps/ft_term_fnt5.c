/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_fnt5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:44:43 by hfrely            #+#    #+#             */
/*   Updated: 2016/05/19 11:45:28 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	exec_right(t_gen *gen, char *buf)
{
	struct winsize	w;
	int				i;

	i = 0;
	(void)buf;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (gen->tcaps->cursor < gen->tcaps->len)
	{
		if (((gen->tcaps->cursor + gen->prompt_len + 1)
					% ((int)w.ws_col) == 0) ||
				gen->tcaps->line[gen->tcaps->cursor] == '\n')
		{
			ft_putstr_fd(tgetstr("kd", NULL), gen->fd);
			ft_putstr_fd(tgetstr("cr", NULL), gen->fd);
		}
		else
			ft_putstr_fd(tgetstr("nd", NULL), gen->fd);
		gen->tcaps->cursor++;
		if ((gen->tcaps->cut1 != -1 || gen->tcaps->cut2 != -1))
		{
			gen->tcaps->cut2++;
			ft_refresh(gen);
		}
	}
}

void	exec_del(t_gen *gen, char *buf)
{
	(void)buf;
	if (gen->tcaps->cursor > 0)
	{
		ft_cpy_list(gen);
		gen->tcaps->line = ft_delchar(gen->tcaps->line, gen->tcaps->cursor - 1);
		ft_refresh(gen);
		gen->tcaps->len--;
		gen->tcaps->cursor--;
		ft_select_left(gen);
		ft_refresh(gen);
	}
}

void	exec_home(t_gen *gen, char *buf)
{
	(void)buf;
	while (gen->tcaps->cursor != 0)
		exec_left(gen, NULL);
}

void	exec_end(t_gen *gen, char *buf)
{
	(void)buf;
	while (gen->tcaps->cursor < gen->tcaps->len)
		exec_right(gen, NULL);
}

void	exec_tab(t_gen *gen, char *buf)
{
	(void)buf;
	if (ft_term_tab(gen))
	{
		gen->tcaps->len = ft_strlen(gen->tcaps->line);
		gen->tcaps->cursor = gen->tcaps->len;
		exec_clean(gen);
		ft_prompt(gen);
		ft_aff_line(gen);
	}
}
