/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 14:42:37 by lscariot          #+#    #+#             */
/*   Updated: 2016/05/17 12:45:07 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_cmd	*ft_create_list(t_cmd *list, char *cmd, int symb, int a[2])
{
	t_cmd *new;
	t_cmd *tmp;

	new = (t_cmd*)malloc(sizeof(*new));
	new->sym = symb;
	new->cmd = ft_strdup(cmd);
	new->in = 1;
	new->out = 1;
	new->aggr = 0;
	if (a[0] || a[1])
		new->aggr = 1;
	new->aggr_one = a[0];
	new->aggr_tow = a[1];
	new->next = NULL;
	new->prev = NULL;
	if (!list)
		return (new);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (list);
}
