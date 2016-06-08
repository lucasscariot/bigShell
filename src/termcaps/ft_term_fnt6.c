/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_fnt6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:59:10 by hfrely            #+#    #+#             */
/*   Updated: 2016/05/21 14:05:02 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		ft_term_count_cursor(t_gen *gen)
{
	int				tmp;
	int				count;
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	tmp = gen->tcaps->cursor;
	count = 1;
	if (ft_strchr(gen->tcaps->line, '\n'))
	{
		while (tmp--)
		{
			if (gen->tcaps->line[tmp] == '\n')
				count++;
		}
		return (count);
	}
	else
	{
		if (gen->tcaps->cursor == gen->tcaps->len)
		{
			return (((gen->tcaps->cursor + gen->prompt_len - 1)
						/ (int)w.ws_col));
		}
		return (((gen->tcaps->cursor + gen->prompt_len) / (int)w.ws_col));
	}
}

int		ft_term_count_row(t_gen *gen)
{
	int				tmp;
	int				count;
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	tmp = 0;
	count = 0;
	if (ft_strchr(gen->tcaps->line, '\n'))
	{
		while (gen->tcaps->line[tmp++])
		{
			if (gen->tcaps->line[tmp] == '\n')
				count++;
		}
		return (count);
	}
	else
		return (((gen->tcaps->len + gen->prompt_len - 1) / (int)w.ws_col));
}

void	exec_up_alt(t_gen *gen, char *buf)
{
	struct winsize	w;

	(void)buf;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if ((gen->tcaps->cursor - (int)w.ws_col) >= 0)
	{
		gen->tcaps->cursor -= (int)w.ws_col;
		ft_putstr_fd(tgetstr("ku", NULL), gen->fd);
	}
}

void	exec_down_alt(t_gen *gen, char *buf)
{
	struct winsize	w;

	(void)buf;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if ((gen->tcaps->cursor + (int)w.ws_col) <= gen->tcaps->len)
	{
		gen->tcaps->cursor += (int)w.ws_col;
		ft_putstr_fd(tgetstr("kd", NULL), gen->fd);
	}
}

void	exec_z_alt(t_gen *gen, char *buf)
{
	(void)buf;
	if (gen->tcaps->cut1 != -1 || gen->tcaps->cut2 != -1)
	{
		gen->tcaps->cut1 = -1;
		gen->tcaps->cut2 = -1;
	}
	else if (gen->tcaps->len != 0)
	{
		gen->tcaps->cut1 = gen->tcaps->cursor;
		gen->tcaps->cut2 = gen->tcaps->cursor;
	}
	ft_refresh(gen);
}
