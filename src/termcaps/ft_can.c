/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_can.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lscariot@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 13:18:10 by lucas             #+#    #+#             */
/*   Updated: 2016/05/17 14:46:58 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int	ft_can(t_gen *gen)
{
	char	buff[2024];
	char	*termtype;
	int		ret;
	char	*term;

	term = (ft_strncmp("iTerm.app", "iTerm.app", 5)
						== 0) ? "linux" : 0;
	if ((termtype = term) == 0)
	{
		ft_putstr_fd("Error", 2);
		exit(1);
	}
	if ((ret = tgetent(buff, termtype)) < 1)
	{
		ft_putstr_fd("no acces termtype\n", 2);
		exit(1);
	}
	tcgetattr(0, &gen->term_ori);
	ft_memcpy(&gen->term, &gen->term_ori, sizeof(struct termios));
	gen->term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, 0, &gen->term);
	return (42);
}
