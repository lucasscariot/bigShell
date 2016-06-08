/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 14:02:28 by hfrely            #+#    #+#             */
/*   Updated: 2016/05/17 12:30:19 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	ft_echo_un(char **tab, int *i, int *n, int *e)
{
	int		j;

	*n = 0;
	*e = 0;
	j = 0;
	*i = 1;
	while (tab[*i] && tab[*i][0] == '-' && (tab[*i][1] == 'n'
				|| tab[*i][1] == 'e'))
	{
		j = 0;
		while (tab[*i][j])
		{
			if (tab[*i][j] == 'n')
				*n = 1;
			else if (tab[*i][j] == 'e')
				*e = 1;
			j++;
		}
		(*i)++;
	}
}

int		ft_echo(t_gen *gen, char **tab)
{
	int		ac;
	int		i;
	int		n;
	int		e;

	(void)gen;
	ac = ft_tablen(tab);
	i = 1;
	ft_echo_un(tab, &i, &n, &e);
	while (tab[i])
	{
		ft_putstr(tab[i]);
		i++;
	}
	if (n == 0)
		ft_putchar('\n');
	return (0);
}
