/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 17:50:20 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/08 14:28:00 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	ft_suppr_deux(t_gen *gen)
{
	if (gen->env->next)
		gen->env->next->prev = gen->env->prev;
	else
		gen->env->next = NULL;
	if (gen->env->prev)
		gen->env->prev->next = gen->env->next;
	else
		gen->env->prev = NULL;
}

char	*ft_suppr_un(t_gen *gen, char *str)
{
	char	*tmp;

	if (gen->env == NULL)
		return (NULL);
	while (gen->env->prev)
		gen->env = gen->env->prev;
	tmp = ft_strjoin(str, "=");
	return (tmp);
}

t_env	*ft_suppr_trois(t_gen *gen)
{
	t_env	*env;

	if (gen->env->next == NULL)
		env = gen->env->prev;
	else
		env = gen->env->next;
	return (env);
}

int		ft_suppr(t_gen *gen, char *str)
{
	char	*tmp;
	t_env	*env;

	tmp = ft_suppr_un(gen, str);
	if (tmp == NULL)
		return (1);
	while (gen->env)
	{
		if (ft_strcmp(gen->env->name, tmp) == 0)
		{
			env = ft_suppr_trois(gen);
			ft_suppr_deux(gen);
			free(gen->env->name);
			free(gen->env->content);
			gen->env = env;
			free(tmp);
			return (0);
		}
		if (gen->env->next == NULL)
			break ;
		gen->env = gen->env->next;
	}
	free(tmp);
	return (1);
}

int		ft_unsetenv(t_gen *gen, char **tab)
{
	int		ac;
	int		i;

	ac = ft_tablen(tab);
	i = 1;
	if (ac < 2)
		return (1);
	while (tab[i])
	{
		ft_suppr(gen, tab[i]);
		i++;
	}
	return (0);
}
