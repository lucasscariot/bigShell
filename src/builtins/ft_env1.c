/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 12:47:22 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/08 19:10:15 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	aff_env(t_gen *gen)
{
	while (gen->env->prev)
		gen->env = gen->env->prev;
	while (gen->env)
	{
		ft_putstr(gen->env->name);
		ft_putstr(gen->env->content);
		ft_putchar('\n');
		if (gen->env->next == NULL)
			break ;
		gen->env = gen->env->next;
	}
}

char	*ft_com_ok(char *str, char *str2)
{
	struct stat		new_stat;
	char			*ptr;
	char			*ptr2;

	ptr = ft_strjoin(str2, "/");
	ptr2 = ft_strjoin(ptr, str);
	free(ptr);
	if (lstat(ptr2, &new_stat) != -1)
		return (ptr2);
	free(ptr2);
	return (NULL);
}

char	**ft_env_new_env(t_gen *gen)
{
	char	**tab;
	int		i;

	while (gen->env->prev)
		gen->env = gen->env->prev;
	i = 0;
	while (gen->env->next)
	{
		gen->env = gen->env->next;
		i++;
	}
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	while (gen->env->prev)
		gen->env = gen->env->prev;
	i = 0;
	while (gen->env->next)
	{
		tab[i] = ft_strjoin(gen->env->name, gen->env->content);
		gen->env = gen->env->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_env_new_tab(char **tab)
{
	char	**new;
	int		i;
	int		j;

	new = (char **)malloc(sizeof(char *) * (ft_tablen(tab) + 1));
	i = 1;
	j = 0;
	while (tab[i])
	{
		new[j] = ft_strdup(tab[i]);
		j++;
		i++;
	}
	new[j] = NULL;
	return (new);
}

int		ft_env_exec_un(pid_t f, char *str, char **av, char **env)
{
	int		status;

	if (f == 0)
	{
		execve(str, av, env);
		exit(0);
	}
	if (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	return (status);
}
