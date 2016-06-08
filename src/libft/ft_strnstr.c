/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 12:13:51 by lscariot          #+#    #+#             */
/*   Updated: 2015/11/26 17:39:30 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str, char *c, size_t n)
{
	size_t	len;

	if (*c == '\0')
		return ((char *)str);
	len = ft_strlen(c);
	while (*str != '\0' && n-- >= len)
	{
		if (*str == *c && ft_memcmp(str, c, len) == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
