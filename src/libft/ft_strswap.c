/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 08:39:36 by lscariot          #+#    #+#             */
/*   Updated: 2016/01/31 09:29:19 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strswap(char **s1, char **s2)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strdup(*s1);
	tmp2 = ft_strdup(*s2);
	free(*s1);
	free(*s2);
	*s1 = ft_strdup(tmp2);
	*s2 = ft_strdup(tmp1);
	free(tmp1);
	free(tmp2);
}
