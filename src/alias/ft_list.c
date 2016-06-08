/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 21:59:42 by hfrely            #+#    #+#             */
/*   Updated: 2016/05/15 20:16:30 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_alias	*ft_create_alias(t_alias *alias, char *cmd, char *replace)
{
	t_alias *new;
	t_alias *tmp;

	new = (t_alias*)malloc(sizeof(*new));
	new->cmd = ft_strdup(cmd);
	new->replace = ft_strdup(replace);
	new->next = NULL;
	new->prev = NULL;
	if (!alias)
		return (new);
	tmp = alias;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (alias);
}
