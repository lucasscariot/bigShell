/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 09:53:04 by lscariot          #+#    #+#             */
/*   Updated: 2016/02/12 12:00:49 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(size + 1);
	if (str == NULL)
		return (NULL);
	while ((int)size + 1 > i)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
