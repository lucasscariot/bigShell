/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:37:35 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/02 11:37:36 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	ft_cmd_deux(t_gen *gen, char **tmp, int nb, int *i)
{
	int		a[2];

	a[0] = 0;
	a[1] = 0;
	gen->cmd = ft_create_list(gen->cmd, *tmp, nb, a);
	free(*tmp);
	*tmp = ft_strnew(1);
	*i = *i + 2;
}

void	ft_cmd_trois(t_gen *gen, char **tmp, int *i, char *line)
{
	int		a[2];

	if (line[*i + 3] == '-')
	{
		a[0] = ft_atoi(&line[*i]);
		a[1] = open("/dev/null", O_RDONLY);
		gen->cmd = ft_create_list(gen->cmd, *tmp, 9, a);
	}
	else
	{
		a[0] = ft_atoi(&line[*i]);
		a[1] = ft_atoi(&line[*i + 3]);
		gen->cmd = ft_create_list(gen->cmd, *tmp, 9, a);
	}
	free(*tmp);
	*tmp = ft_strnew(1);
	*i = *i + 4;
}

void	ft_cmd_quatre(t_gen *gen, char **tmp)
{
	int		a[2];

	a[0] = 0;
	a[1] = 0;
	gen->cmd = ft_create_list(gen->cmd, *tmp, 0, a);
}

void	ft_cmd_split(t_gen *gen, char *line)
{
	char	*tmp;
	int		i;
	int		nb;
	int		j;

	tmp = ft_strnew(1);
	if (!line)
		return ;
	i = 0;
	j = ft_strlen(line);
	while (line[i] && j >= i)
	{
		if (ft_check_quote_cmd(line[i - 1], line[i]))
		{
		}
		else if ((nb = ft_check_select(line, i)))
			ft_cmd_un(gen, &tmp, nb, &i);
		else if ((nb = ft_check_select_bis(line, i)))
			ft_cmd_deux(gen, &tmp, nb, &i);
		else if ((nb = ft_check_select_tow(line, i)))
			ft_cmd_trois(gen, &tmp, &i, line);
		tmp = ft_addchar_back(tmp, line[i]);
		i++;
	}
	ft_cmd_quatre(gen, &tmp);
}
