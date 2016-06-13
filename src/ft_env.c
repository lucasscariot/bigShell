/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 09:23:49 by lscariot          #+#    #+#             */
/*   Updated: 2016/06/13 19:39:19 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_env	*ft_env_list(t_env *env, char *name, char *content)
{
	t_env *new;
	t_env *tmp;

	if (!name)
		return (env);
	new = (t_env*)malloc(sizeof(*new));
	new->name = ft_strjoin(name, "=");
	if (!(new->content = ft_strdup(content)))
		new->content = ft_strnew(0);
	new->next = NULL;
	new->prev = NULL;
	if (env == NULL)
		return (new);
	tmp = env;
	while (tmp->next && ft_strcmp(tmp->name, new->name))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(tmp->name, new->name))
		tmp->content = ft_strdup(new->content);
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
	return (env);
}

void	ft_check_env(t_gen *gen)
{
	t_env	*tmp;
	int		check;

	tmp = gen->env;
	check = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "SHLVL="))
		{
			tmp->content = ft_strreplace(tmp->content,
					ft_itoa(ft_atoi(tmp->content) + 1));
			check = 1;
		}
		tmp = tmp->next;
	}
	if (!check)
	{
		gen->env = ft_env_list(gen->env, "SHLVL", "1");
	}
}

t_env	*ft_save_env(char **env)
{
	char	**split;
	t_env	*envt;
	int		i;

	i = 0;
	envt = NULL;
	while (env[i])
	{
		split = ft_strsplit(env[i++], '=');
		envt = ft_env_list(envt, split[0], split[1]);
	}
	return (envt);
}
