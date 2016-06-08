/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 22:35:33 by hfrely            #+#    #+#             */
/*   Updated: 2016/05/18 10:46:36 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*ft_getenv(t_gen *gen, char *str)
{
	char	*new;

	if (gen->env == NULL)
		return (NULL);
	while (gen->env->prev)
		gen->env = gen->env->prev;
	while (gen->env)
	{
		if (ft_strcmp(gen->env->name, str) == 0)
		{
			new = ft_strdup(gen->env->content);
			return (new);
		}
		if (gen->env->next == NULL)
			break ;
		gen->env = gen->env->next;
	}
	return (NULL);
}

void	ft_modenv(t_gen *gen, char *name, char *content)
{
	while (gen->env->prev)
		gen->env = gen->env->prev;
	while (gen->env)
	{
		if (ft_strcmp(gen->env->name, name) == 0)
		{
			if (gen->env->content)
				free(gen->env->content);
			gen->env->content = ft_strdup(content);
		}
		if (gen->env->next == NULL)
			break ;
		gen->env = gen->env->next;
	}
}
