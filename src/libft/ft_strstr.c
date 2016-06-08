/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 12:15:11 by lscariot          #+#    #+#             */
/*   Updated: 2015/11/27 03:20:01 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *c)
{
	size_t	len;

	if (*c == '\0')
		return ((char *)str);
	len = ft_strlen(c);
	while (*str != '\0')
	{
		if (*str == *c && ft_memcmp(str, c, len) == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
