/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:57:27 by lscariot          #+#    #+#             */
/*   Updated: 2015/11/27 03:17:34 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((unsigned char)s1[i] != '\0' && (unsigned char)s2[i] != '\0'
			&& (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	return ((int)(unsigned char)s1[i] - (unsigned char)s2[i]);
}
