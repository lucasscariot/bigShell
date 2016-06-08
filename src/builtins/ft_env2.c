/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 12:48:35 by hfrely            #+#    #+#             */
/*   Updated: 2016/05/17 15:39:34 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		ft_env_exec(t_gen *gen, char *str, char **tab, char **envi)
{
	pid_t	f;
	char	**env;
	char	**av;
	int		i;
	int		status;

	i = 0;
	status = 1;
	f = fork();
	if (envi != NULL)
		env = envi;
	else
		env = ft_env_new_env(gen);
	av = ft_env_new_tab(tab);
	status = ft_env_exec_un(f, str, av, env);
	ft_freetab(av);
	return (status);
}

int		ft_env_deux(t_gen *gen, char **tab)
{
	char	*tmp;
	char	**split;
	int		i;

	if ((tmp = ft_getenv(gen, "PATH=")) == NULL)
		return (1);
	split = ft_strsplit(tmp, ':');
	free(tmp);
	i = 0;
	if (tab[0] && (tab[1][0] == '.' || tab[1][0] == '/'))
		if (!check_exec(tab[1]))
			ft_env_exec(gen, tab[1], tab, NULL);
	while (split[i])
	{
		if ((tmp = ft_com_ok(tab[1], split[i])) == NULL)
		{
			i++;
			continue ;
		}
		i = ft_env_exec(gen, tmp, tab, NULL);
		free(tmp);
		return (i);
	}
	return (1);
}

void	ft_env_i_un(t_gen *gen, char **tab, char **env)
{
	if (tab[0] && (tab[2][0] == '.' || tab[2][0] == '/'))
		if (!check_exec(tab[2]))
			ft_env_exec(gen, tab[2], tab, env);
}

int		ft_env_i(t_gen *gen, char **env, char **tab)
{
	char	*tmp;
	char	**split;
	char	**av;
	int		i;

	if ((tmp = ft_getenv(gen, "PATH=")) == NULL)
		return (1);
	split = ft_strsplit(tmp, ':');
	free(tmp);
	ft_env_i_un(gen, tab, env);
	i = 0;
	while (split[i])
	{
		if ((tmp = ft_com_ok(tab[2], split[i])) == NULL)
		{
			i++;
			continue ;
		}
		av = ft_env_new_tab(tab);
		i = ft_env_exec(gen, tmp, av, env);
		ft_freetab(av);
		free(tmp);
		return (i);
	}
	return (1);
}

char	**ft_count_env_i(char **tab)
{
	char	**new;
	int		i;
	int		j;
	int		check;

	i = 0;
	j = 0;
	check = 0;
	new = (char **)malloc(sizeof(char *) * 20);
	while (tab[i])
	{
		if (ft_strchr(tab[i], '=') != NULL)
		{
			new[j] = ft_strdup(tab[i]);
			j++;
			check = 1;
		}
		else if (check == 1)
			break ;
		i++;
	}
	new[j] = NULL;
	return (new);
}
