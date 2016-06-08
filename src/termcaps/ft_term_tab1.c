/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_tab1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:04:08 by hfrely            #+#    #+#             */
/*   Updated: 2016/05/17 18:40:34 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*ft_after_slash(char *str)
{
	int		i;
	int		j;
	int		tmp;
	char	*new;

	i = 0;
	j = 0;
	tmp = 0;
	while (str[i])
	{
		if (str[i] == '/')
			tmp = i;
		i++;
	}
	new = (char *)malloc(sizeof(char) * (i - tmp + 1));
	tmp++;
	while (tmp <= i)
	{
		new[j] = str[tmp];
		tmp++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	*ft_slash(char *str)
{
	int		i;
	int		tmp;
	char	*new;

	i = 0;
	tmp = 0;
	while (str[i])
	{
		if (str[i] == '/')
			tmp = i;
		i++;
	}
	new = (char *)malloc(sizeof(char) * (tmp + 1));
	i = 0;
	while (tmp >= i)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int		ft_isdir(char *name)
{
	DIR		*directory;
	char	*tmp;

	if (name[0] != '.' || name[0] != '/')
		tmp = ft_strjoin("./", name);
	else
		tmp = ft_strdup(name);
	directory = opendir(tmp);
	free(tmp);
	if (directory != NULL)
	{
		closedir(directory);
		return (1);
	}
	return (0);
}

void	ft_term_add_tab_un(t_gen *gen, int i)
{
	while (gen->tcaps->line[i] != ' ')
	{
		gen->tcaps->line = ft_delchar(gen->tcaps->line, i);
		i--;
	}
}

void	ft_term_add_tab(t_gen *gen, t_norm *norm)
{
	char	*tmp;
	char	*line;
	int		i;
	char	*tmp2;

	if (norm->nb)
		tmp = ft_slash(norm->str);
	else
		tmp = ft_strdup("");
	i = ft_strlen(gen->tcaps->line) - 1;
	ft_term_add_tab_un(gen, i);
	line = ft_strjoin(gen->tcaps->line, tmp);
	free(gen->tcaps->line);
	gen->tcaps->line = ft_strjoin(line, norm->tmp);
	free(line);
	line = ft_strjoin(tmp, norm->tmp);
	if (ft_isdir(line))
	{
		tmp2 = ft_strjoin(gen->tcaps->line, "/");
		free(gen->tcaps->line);
		gen->tcaps->line = ft_strdup(tmp2);
		free(tmp2);
	}
}
