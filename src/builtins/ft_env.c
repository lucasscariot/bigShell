/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 14:06:29 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/14 21:32:08 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		aff_env(t_env *env)
{
	if (env == NULL)
		return (0);
	while (env->prev)
		env = env->prev;
	while (env)
	{
		ft_putstr(env->name);
		ft_putstr(env->content);
		ft_putchar('\n');
		if (env->next == NULL)
			break ;
		env = env->next;
	}
	return (0);
}

char	**ft_env_new_env(t_env *env)
{
	char	**tab;
	int		i;

	if (env == NULL)
		return (NULL);
	while (env->prev)
		env = env->prev;
	i = 0;
	while (env->next && (env = env->next))
		i++;
	tab = (char **)malloc(sizeof(char *) * (i + 2));
	while (env->prev)
		env = env->prev;
	i = 0;
	while (env)
	{
		tab[i] = ft_strjoin(env->name, env->content);
		i++;
		if (env->next == NULL)
			break ;
		env = env->next;
	}
	tab[i] = NULL;
	return (tab);
}

t_env	*ft_cpy_env(t_env *env)
{
	t_env	*new;

	if (env == NULL)
		return (NULL);
	while (env->prev)
		env = env->prev;
	while (env)
	{
		new = ft_env_list(new, ft_delchar(ft_strdup(env->name),
					ft_strlen(env->name) - 1), ft_strdup(env->content));
		if (env->next == NULL)
			break ;
		env = env->next;
	}
	return (new);
}

char	**ft_is_exec_for_exec(char **tab, int i)
{
	int		j;
	int		k;
	char	**new;

	j = i;
	k = 0;
	while (tab[i])
	{
		k++;
		i++;
	}
	new = (char **)malloc(sizeof(char *) * (k + 1));
	k = 0;
	while (tab[j])
	{
		new[k] = ft_strdup(tab[j]);
		k++;
		j++;
	}
	new[k] = NULL;
	return (new);
}

int		ft_env(t_gen *gen, char **tab)
{
	int		ac;
	t_env	*env;
	int		i;
	char	**split;

	i = 1;
	ac = ft_tablen(tab);
	env = ft_cpy_env(gen->env);
	if (ac > 1 && tab[i][0] == '-' && tab[i][1] == 'i' && i++)
		gen->env = NULL;
	else
		gen->env = ft_cpy_env(gen->env);
	while (tab[i] && ft_strchr(tab[i], '='))
	{
		split = ft_strsplit(tab[i], '=');
		gen->env = ft_env_list(gen->env, split[0], split[1]);
		ft_freetab(split);
		i++;
	}
	if (ft_exec_phase_one(gen, ft_is_exec_for_exec(tab, i), ft_env_new_env(gen->env))
			== -1)
		aff_env(gen->env);
	gen->env = ft_cpy_env(env);
	return (0);
}
