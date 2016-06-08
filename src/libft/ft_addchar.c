/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 14:43:25 by hfrely            #+#    #+#             */
/*   Updated: 2016/05/07 16:02:14 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_addchar(char *str, int c, char fuck)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((int)ft_strlen(str) < c)
		return (str);
	new = ft_strnew(ft_strlen(str) + 1);
	while (str[i])
	{
		if (i == c)
		{
			new[j] = fuck;
			j++;
		}
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}
