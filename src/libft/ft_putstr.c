/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/04 02:03:48 by lucas             #+#    #+#             */
/*   Updated: 2016/04/22 09:45:05 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(const char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr("(null)");
		return ;
	}
	while (str[i] != '\0')
		ft_putchar(str[i++]);
}

void	debug(int i)
{
	ft_putcolor("\n---------------->  ", RED);
	ft_putstr("DEBUG N'");
	ft_putnbr(i);
	ft_putcolor("  <----------------\n", RED);
}
