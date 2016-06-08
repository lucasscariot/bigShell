/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 18:15:19 by lscariot          #+#    #+#             */
/*   Updated: 2016/05/12 14:49:52 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_caps	*ft_create_caps(t_caps *tcaps)
{
	t_caps	*new;
	t_caps	*tmp;

	new = (t_caps*)malloc(sizeof(*new));
	new->line = ft_strnew(1);
	new->cursor = 0;
	new->len = 0;
	new->cut1 = -1;
	new->cut2 = -1;
	new->row = 0;
	new->next = NULL;
	new->prev = NULL;
	if (tcaps == NULL)
		return (new);
	tmp = tcaps;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (new);
}

void	ft_cpy_list(t_gen *gen)
{
	char	*str;
	int		tmp_cur;
	int		tmp_len;
	int		tmp_row;

	if (gen->tcaps->next == NULL)
		return ;
	str = ft_strdup(gen->tcaps->line);
	tmp_cur = gen->tcaps->cursor;
	tmp_len = gen->tcaps->len;
	tmp_row = gen->tcaps->row;
	while (gen->tcaps->next)
		gen->tcaps = gen->tcaps->next;
	free(gen->tcaps->line);
	gen->tcaps->line = ft_strdup(str);
	gen->tcaps->row = tmp_row;
	gen->tcaps->cursor = tmp_cur;
	gen->tcaps->len = tmp_len;
	free(str);
}

void	ft_add_tcaps(t_gen *gen, char *buf)
{
	char	*tmp;
	int		i;

	i = 0;
	ft_cpy_list(gen);
	if (gen->tcaps->cursor < gen->tcaps->len)
		while (buf[i])
		{
			gen->tcaps->line = ft_addchar(gen->tcaps->line, \
				gen->tcaps->cursor, buf[i]);
			gen->tcaps->cursor++;
			gen->tcaps->len++;
			i++;
		}
	else
	{
		while (buf[i++])
		{
			gen->tcaps->cursor++;
			gen->tcaps->len++;
		}
		tmp = ft_strjoin(gen->tcaps->line, buf);
		free(gen->tcaps->line);
		gen->tcaps->line = tmp;
	}
}
