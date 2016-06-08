/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_fnt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <lscariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 08:37:22 by lscariot          #+#    #+#             */
/*   Updated: 2016/05/19 12:45:58 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	exec_c_alt(t_gen *gen, char *buf)
{
	int		tmp;

	(void)buf;
	if ((gen->tcaps->cut1 == -1 && gen->tcaps->cut2 == -1)
			|| (gen->tcaps->cut1 == 0 && gen->tcaps->cut2 == 0)
			|| (gen->tcaps->cut1 == gen->tcaps->len
				&& gen->tcaps->cut2 == gen->tcaps->len))
		return ;
	tmp = gen->tcaps->cut2;
	gen->tcaps->cut2 = gen->tcaps->cut1;
	gen->tcaps->cut1 = tmp;
	gen->copy = ft_strsub(gen->tcaps->line, gen->tcaps->cut1,
			gen->tcaps->cut2 + 1 - gen->tcaps->cut1);
	exec_z_alt(gen, NULL);
	ft_refresh(gen);
}

void	exec_left_alt(t_gen *gen, char *buf)
{
	(void)buf;
	exec_left(gen, NULL);
	if (gen->tcaps->line[gen->tcaps->cursor] == ' ')
	{
		while (gen->tcaps->line[gen->tcaps->cursor] == ' ')
			exec_left(gen, NULL);
	}
	while (gen->tcaps->line[gen->tcaps->cursor - 1] != ' '
			&& gen->tcaps->cursor > 0)
		exec_left(gen, NULL);
}

void	exec_right_alt(t_gen *gen, char *buf)
{
	(void)buf;
	exec_right(gen, NULL);
	if (gen->tcaps->line[gen->tcaps->cursor] == ' ')
	{
		while (gen->tcaps->line[gen->tcaps->cursor] == ' ')
			exec_right(gen, NULL);
	}
	while (gen->tcaps->line[gen->tcaps->cursor] != ' '
			&& gen->tcaps->cursor < gen->tcaps->len)
		exec_right(gen, NULL);
}

void	exec_write(t_gen *gen, char *buf)
{
	int				tmp;

	if (!ft_isprint(buf[0]) && buf[0] != '\n')
		return ;
	exec_clean(gen);
	ft_add_tcaps(gen, buf);
	ft_prompt(gen);
	ft_select_right(gen);
	ft_aff_line(gen);
	tmp = gen->tcaps->len;
	while (tmp > gen->tcaps->cursor)
	{
		ft_putstr_fd(tgetstr("le", NULL), gen->fd);
		tmp--;
	}
}

void	exec_clean(t_gen *gen)
{
	struct winsize	w;
	int				tmp;
	int				i;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (ft_strchr(gen->tcaps->line, '\n'))
		i = ft_term_count_row(gen);
	else
		i = ft_term_count_cursor(gen);
	while (i-- > 0)
		ft_putstr_fd(tgetstr("ku", NULL), gen->fd);
	if ((gen->tcaps->len + gen->prompt_len) % ((int)w.ws_col) == 0)
		gen->tcaps->row++;
	tmp = gen->tcaps->len;
	while (tmp--)
		ft_putstr_fd(tgetstr("dl", NULL), gen->fd);
	tmp = tgetnum("co");
	while (tmp--)
		ft_putstr_fd(tgetstr("kl", NULL), gen->fd);
}
