/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_etou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 17:47:11 by lscariot          #+#    #+#             */
/*   Updated: 2016/06/13 20:46:31 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*check_cmd_path(char **tab, char **env)
{
	char	*tmp;
	char	**split;
	int		i;
	char	*tmp2;

	i = 0;
	while (env && *env && ft_strncmp(env[i], "PATH=", 5))
		i++;
	tmp = ft_strdup(env[i] + 5);
	if (*tmp == '\0')
		return (NULL);
	split = ft_strsplit(tmp, ':');
	free(tmp);
	i = 0;
	while (split[i])
	{
		tmp2 = ft_strjoin(split[i], "/");
		tmp = ft_strjoin(tmp2, tab[0]);
		free(tmp2);
		if (check_exec(tmp) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

char	*ft_addchar_back(char *str, char fuck)
{
	char	*new;
	int		i;

	if (str == NULL)
		return (ft_strdup(&fuck));
	i = 0;
	new = ft_strnew(ft_strlen(str) + 1);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = fuck;
	new[i + 1] = '\0';
	free(str);
	return (new);
}

int		ft_ouou(t_gen *gen)
{
	if (gen->status != 0)
		return (0);
	while (gen->cmd->sym == 8)
		gen->cmd = gen->cmd->next;
	return (0);
}

int		ft_etet(t_gen *gen)
{
	if (gen->status == 0)
		return (0);
	while (gen->cmd->sym == 7)
		gen->cmd = gen->cmd->next;
	return (0);
}

int		ft_etou(t_gen *gen)
{
	if (gen->cmd->sym == 7)
		return (ft_etet(gen));
	else if (gen->cmd->sym == 8)
	{
		while (gen)
			return (ft_ouou(gen));
	}
	return (0);
}
