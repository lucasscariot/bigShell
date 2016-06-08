/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_fnt4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:44:01 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/02 14:46:40 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		exec_enter_un(t_gen *gen)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	while (gen->tcaps->line[i])
	{
		if (gen->tcaps->line[i] == '\\')
			i = i + 2;
		if (ft_exec_quote(gen->tcaps->line[i], 0))
		{
			check = 1;
			i++;
			continue ;
		}
		else
			check = 0;
		i++;
	}
	return (check);
}

void	exec_enter(t_gen *gen, char *buf)
{
	int				i;
	int				check;

	(void)buf;
	ft_cpy_list(gen);
	check = exec_enter_un(gen);
	i = ft_term_count_cursor(gen);
	while (i < gen->tcaps->row && !check)
	{
		ft_putstr_fd(tgetstr("kd", NULL), gen->fd);
		i++;
	}
	if (check == 0)
	{
		if (check_redi_exec(gen, gen->tcaps->line))
			check = 1;
	}
	ft_exec_quote('c', 1);
	i = ft_strlen(gen->tcaps->line);
	if (gen->tcaps->line[i - 1] == '\\')
	{
		exec_write(gen, buf);
		gen->tcaps->row++;
	}
	else if (check == 0)
		gen->stop = 0;
	else
	{
		exec_write(gen, buf);
		gen->tcaps->row++;
	}
}

void	exec_up(t_gen *gen, char *buf)
{
	(void)buf;
	if (gen->tcaps->prev != NULL)
	{
		exec_clean(gen);
		ft_prompt(gen);
		gen->tcaps = gen->tcaps->prev;
		ft_aff_line(gen);
		gen->tcaps->cursor = gen->tcaps->len;
	}
}

void	exec_down(t_gen *gen, char *buf)
{
	if (gen->tcaps->next != NULL)
	{
		exec_clean(gen);
		ft_prompt(gen);
		gen->tcaps = gen->tcaps->next;
		ft_aff_line(gen);
		gen->tcaps->cursor = gen->tcaps->len;
	}
	(void)buf;
}

void	exec_left(t_gen *gen, char *buf)
{
	int i;

	i = -gen->prompt_len + 1;
	(void)buf;
	if (gen->tcaps->cursor > 0)
	{
		gen->tcaps->cursor--;
		ft_putstr_fd(tgetstr("le", NULL), gen->fd);
		if ((gen->tcaps->cut1 || gen->tcaps->cut2)
				&& gen->tcaps->cut2 > gen->tcaps->cursor)
		{
			gen->tcaps->cut2--;
			ft_refresh(gen);
		}
		if (gen->tcaps->line[gen->tcaps->cursor] == '\n')
		{
			ft_putstr_fd(tgetstr("ku", NULL), gen->fd);
			while (gen->tcaps->line[i - 1] != '\n')
			{
				ft_putstr_fd(tgetstr("nd", NULL), gen->fd);
				i++;
			}
		}
	}
}
