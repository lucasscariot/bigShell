/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_tab2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 18:40:59 by hfrely            #+#    #+#             */
/*   Updated: 2016/05/17 18:47:52 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	ft_point_slash_un(t_gen *gen, t_norm *norm)
{
	int				i;
	struct dirent	*dp;

	if (norm->dir == NULL)
		return ;
	i = 0;
	while ((dp = readdir(norm->dir)) != NULL)
	{
		if (i > 1)
			break ;
		if (ft_strncmp(dp->d_name, norm->tmp2, ft_strlen(norm->tmp2)) == 0)
		{
			free(norm->tmp);
			norm->tmp = ft_strdup(dp->d_name);
			i++;
		}
	}
	norm->nb = 0;
	if (ft_strchr(norm->str, '/'))
		norm->nb = 1;
	if (i == 1)
		ft_term_add_tab(gen, norm);
	if (i > 1)
		free(norm->tmp);
}

void	ft_point_slash_deux(t_gen *gen, t_norm *norm)
{
	if (ft_strchr(norm->str, '/'))
	{
		norm->tmp = ft_slash(norm->str);
		norm->tmp2 = ft_after_slash(norm->str);
		norm->dir = opendir(norm->tmp);
		ft_point_slash_un(gen, norm);
	}
	else
	{
		norm->tmp = ft_strdup("a");
		norm->dir = opendir(".");
		ft_point_slash_un(gen, norm);
	}
}

void	ft_point_slash(t_gen *gen, char *str, int nb)
{
	t_norm			*norm;

	norm = (t_norm *)malloc(sizeof(*norm));
	norm->str = ft_strdup(str);
	norm->nb = nb;
	if (nb)
	{
		norm->tmp = ft_slash(str);
		norm->tmp2 = ft_after_slash(str);
		norm->dir = opendir(norm->tmp);
		ft_point_slash_un(gen, norm);
	}
	else
		ft_point_slash_deux(gen, norm);
}
