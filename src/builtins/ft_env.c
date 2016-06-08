/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 14:06:29 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/08 19:10:14 by lscariot         ###   ########.fr       */
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
		debug(42);
		ft_putstr(env->name);
		ft_putstr(env->content);
		ft_putchar('\n');
		if (env->next == NULL)
			break ;
		env = env->next;
	}
	return (0);
}

char    **ft_env_new_env(t_gen *gen)
{
	char	**tab;
	int		i;

	while (gen->env->prev)
		gen->env = gen->env->prev;
	i = 0;
	while (gen->env->next)
	{
		i++;
		if (gen->env->next == NULL)
			break ;
		gen->env = gen->env->next;
	}
	tab = (char **)malloc(sizeof(char *) * (i + 2));
	while (gen->env->prev)
		gen->env = gen->env->prev;
	i = 0;
	while (gen->env)
	{
		tab[i] = ft_strjoin(gen->env->name, gen->env->content);
		i++;
		if (gen->env->next == NULL)
			break ;
		gen->env = gen->env->next;
	}
	tab[i] = NULL;
	return (tab);
}

t_env	*ft_cpy_env(t_env *env)
{
	t_env	*new;

	while (env->prev)
		env = env->prev;
	while (env)
	{
		new = ft_env_list(new, ft_delchar(ft_strdup(env->name),
					ft_strlen(env->name) - 1), env->content);
		if (env->next == NULL)
			break ;
		env = env->next;
	}
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
		debug(1);
		split = ft_strsplit(tab[i], '=');
		env = ft_env_list(env, split[0], split[1]);
		debug(1);
		i++;
	}
	debug(2);
	if (arg == 0)
		aff_env(env);
	else
	{
		return (1);
	}
	return (0);
}
