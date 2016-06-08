/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_etou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 17:47:11 by lscariot          #+#    #+#             */
/*   Updated: 2016/05/17 12:36:19 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*ft_addchar_back(char *str, char fuck)
{
	char	*new;
	int		i;

	if (str == NULL)
		return (ft_strdup(&fuck));
	i = 0;
	new = ft_strnew(ft_strlen(str) + 1);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = fuck;
	new[i + 1] = '\0';
	free(str);
	return (new);
}

int		ft_ouou(t_gen *gen)
{
	if (gen->status != 0)
		return (0);
	while (gen->cmd->sym == 8)
		gen->cmd = gen->cmd->next;
	return (0);
}

int		ft_etet(t_gen *gen)
{
	if (gen->status == 0)
		return (0);
	while (gen->cmd->sym == 7)
		gen->cmd = gen->cmd->next;
	return (0);
}

int		ft_etou(t_gen *gen)
{
	if (gen->cmd->sym == 7)
		return (ft_etet(gen));
	else if (gen->cmd->sym == 8)
	{
		while (gen)
			return (ft_ouou(gen));
	}
	return (0);
}
