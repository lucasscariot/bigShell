/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <lscariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 15:39:20 by lscariot          #+#    #+#             */
/*   Updated: 2016/05/19 12:38:32 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	ft_term_exec(t_gen *gen, char *buf, enum e_key key)
{
	static t_exec	*exec[BASIC_KEY + 1] = {
	&exec_enter,
	&exec_up,
	&exec_down,
	&exec_left,
	&exec_right,
	&exec_del,
	&exec_home,
	&exec_end,
	&exec_tab,
	&exec_left_alt,
	&exec_right_alt,
	&exec_up_alt,
	&exec_down_alt,
	&exec_z_alt,
	&exec_c_alt,
	&exec_x_alt,
	&exec_v_alt,
	&exec_ctrl_l,
	&exec_ctrl_d,
	&exec_write
	};

	(*exec[key])(gen, buf);
}

int		ft_term_check_key(char *buf, char **tab)
{
	int		i;

	i = 0;
	while (i < BASIC_KEY)
	{
		if (!ft_strcmp(buf, tab[i]))
			return (i);
		++i;
	}
	return (BASIC_KEY);
}

int		ft_term_add_key_un(char **tab, char *buf)
{
	if (tab[0] == NULL)
	{
		tab[ENTER_KEY] = ft_init_key('\n', 0, 0, 0);
		tab[UP_KEY] = ft_init_key(27, 91, 65, 0);
		tab[DOWN_KEY] = ft_init_key(27, 91, 66, 0);
		tab[LEFT_KEY] = ft_init_key(27, 91, 68, 0);
		tab[RIGHT_KEY] = ft_init_key(27, 91, 67, 0);
		tab[DEL_KEY] = ft_init_key(127, 0, 0, 0);
		tab[HOME_KEY] = ft_init_key(27, 91, 72, 0);
		tab[END_KEY] = ft_init_key(27, 91, 70, 0);
		tab[TAB_KEY] = ft_init_key(9, 0, 0, 0);
		tab[LEFT_ALT_KEY] = ft_init_key(27, 27, 91, 68);
		tab[RIGHT_ALT_KEY] = ft_init_key(27, 27, 91, 67);
		tab[UP_ALT_KEY] = ft_init_key(27, 91, 53, 126);
		tab[DOWN_ALT_KEY] = ft_init_key(27, 91, 54, 126);
		tab[ALT_Z] = ft_init_key(-50, -87, 0, 0);
		tab[ALT_C] = ft_init_key(-61, -89, 0, 0);
		tab[ALT_X] = ft_init_key(-30, -119, -120, 0);
		tab[ALT_V] = ft_init_key(-30, -120, -102, 0);
		tab[CTRL_L] = ft_init_key(12, 0, 0, 0);
		tab[CTRL_D] = ft_init_key(4, 0, 0, 0);
		tab[BASIC_KEY] = NULL;
	}
	return (ft_term_check_key(buf, tab));
}

int		ft_term_add_key(char *buf)
{
	static char *tab[BASIC_KEY + 1] = {NULL};

	return (ft_term_add_key_un(tab, buf));
}

void	ft_exec_key(char *buf, t_gen *gen)
{
	int		key;

	key = ft_term_add_key(buf);
	ft_term_exec(gen, buf, key);
}
