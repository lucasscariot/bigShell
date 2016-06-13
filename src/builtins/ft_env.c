/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 14:06:29 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/13 10:27:35 by hfrely           ###   ########.fr       */
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

char    **ft_env_new_env(t_env *env)
{
	char	**tab;
	int		i;

	if (env == NULL)
		return (NULL);
	while (env->prev)
		env = env->prev;
	i = 0;
	while (env->next)
	{
		i++;
		if (env->next == NULL)
			break ;
		env = env->next;
	}
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
	while (env->next)
	{
		new = ft_env_list(new, ft_delchar(ft_strdup(env->name),
					ft_strlen(env->name) - 1), ft_strdup(env->content));
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
	int		arg;
	char	**split;

	i = 1;
	arg = 0;
	ac = ft_tablen(tab);
	if (ac == 1)
		return (aff_env(gen->env));
	if (tab[i][0] == '-' && tab[i][1] == 'i')
	{
		i++;
		arg = 1;
	}
	if (arg == 1)
		env = NULL;
	else
		env = ft_cpy_env(gen->env);
	arg = 0;
	while (tab[i])
	{
		if (!ft_strchr(tab[i], '='))
		{
			arg = 1;
			break ;
		}
		split = ft_strsplit(tab[i], '=');
		env = ft_env_list(env, split[0], split[1]);
		ft_freetab(split);
		i++;
	}
	if (arg == 1)
	{
		split = ft_is_exec_for_exec(tab, i);
		ft_exec_phase_one(gen, split, ft_env_new_env(env));
	}
	else
		aff_env(env);
	return (0);
}
