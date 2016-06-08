/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_source.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 15:17:53 by hfrely            #+#    #+#             */
/*   Updated: 2016/05/17 15:22:30 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		ft_cmd_source(char *str)
{
	char	**tab;

	tab = ft_strsplit_mc(str, " \t");
	if (ft_strcmp(tab[0], "source") == 0)
	{
		ft_freetab(tab);
		return (1);
	}
	ft_freetab(tab);
	return (0);
}
