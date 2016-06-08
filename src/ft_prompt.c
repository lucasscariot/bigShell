/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 12:15:28 by lscariot          #+#    #+#             */
/*   Updated: 2016/05/17 12:31:15 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	prompt_base(t_gen *gen)
{
	gen->prompt = ft_strdup("THE21SH $> ");
	gen->prompt_len = 11;
}

char	*ft_current_dir(char *path)
{
	char	**tab;
	char	*tmp;
	int		i;

	i = 0;
	tab = ft_strsplit(path, '/');
	while (tab[i])
		i++;
	if (i == 0)
		return (path);
	i--;
	free(path);
	tmp = ft_strdup(tab[i]);
	ft_freetab(tab);
	return (tmp);
}

void	ft_update_prompt(t_gen *gen)
{
	char	*tmp;

	if (gen->prompt)
		free(gen->prompt);
	tmp = ft_getenv(gen, "PWD=");
	if (tmp == NULL)
	{
		prompt_base(gen);
		return ;
	}
	gen->prompt = ft_current_dir(tmp);
	gen->prompt_len = ft_strlen(gen->prompt);
	gen->prompt_len += 4;
}

int		ft_prompt(t_gen *gen)
{
	if (gen->status == 0)
		ft_putcolor("✓  ", GREEN);
	else
		ft_putcolor("✗  ", RED);
	ft_putcolor(gen->prompt, "\e[93m");
	ft_putstr(" ");
	if (!gen)
		return (0);
	return (0);
}
