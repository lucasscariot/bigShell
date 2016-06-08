/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 14:53:08 by hfrely            #+#    #+#             */
/*   Updated: 2016/05/17 18:47:51 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	ft_term_tab_dir(t_gen *gen, char *str)
{
	if (ft_strncmp(str, "./", 2) == 0)
		ft_point_slash(gen, str, 1);
	else if (ft_strncmp(str, ".", 1) == 0)
		ft_point_slash(gen, str, 1);
	else if (ft_strncmp(str, "/", 1) == 0)
		ft_point_slash(gen, str, 1);
}

int		ft_term_tab_path_ok_un(t_gen *gen, char *tmp)
{
	if (gen->tmp_tab != NULL)
		free(gen->tmp_tab);
	gen->tmp_tab = ft_strdup(tmp);
	free(tmp);
	return (1);
}

int		ft_term_tab_path_ok(t_gen *gen, char *str, char *name)
{
	DIR				*dir;
	struct dirent	*dp;
	int				i;
	char			*tmp;

	dir = opendir(str);
	i = 0;
	tmp = ft_strdup("a");
	while ((dp = readdir(dir)) != NULL)
	{
		if (ft_strncmp(dp->d_name, name, ft_strlen(name)) == 0)
		{
			free(tmp);
			tmp = ft_strdup(dp->d_name);
			i++;
		}
	}
	if (i == 1)
		return (ft_term_tab_path_ok_un(gen, tmp));
	free(tmp);
	if (i > 1)
		return (1);
	return (0);
}

void	ft_term_add_path(t_gen *gen)
{
	int		i;
	char	*tmp;

	if (gen->tmp_tab == NULL)
		return ;
	i = ft_strlen(gen->tcaps->line) - 1;
	while (gen->tcaps->line[i] != ' ')
	{
		gen->tcaps->line = ft_delchar(gen->tcaps->line, i);
		i--;
	}
	tmp = ft_strjoin(gen->tcaps->line, gen->tmp_tab);
	free(gen->tcaps->line);
	gen->tcaps->line = ft_strdup(tmp);
	free(tmp);
	free(gen->tmp_tab);
	gen->tmp_tab = NULL;
}

int		ft_term_tab(t_gen *gen)
{
	char	**tab;
	int		i;

	if (gen->tcaps->cursor != gen->tcaps->len)
		return (0);
	tab = ft_strsplit_mc(gen->tcaps->line, " ");
	i = 0;
	if (tab[i] == NULL)
		return (0);
	while (tab[i + 1] != NULL)
		i++;
	ft_term_tab_dir(gen, tab[i]);
	return (1);
}
