/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 13:45:43 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/06 14:09:15 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	ft_setterm(t_gen *gen, int i)
{
	if (i == 1)
		tcsetattr(0, 0, &gen->term_ori);
	else if (i == 0)
		tcsetattr(0, 0, &gen->term);
}

void	ft_not_found(t_gen *gen, char *str)
{
	ft_putstr(SH);
	ft_putstr(": command not found: ");
	ft_putendl(str);
	gen->status = 1;
}

void	ft_exec_phase_three(t_gen *gen, char **tab, char **env)
{
	if (set_redirection(gen) == 1)
		exit(1);
	if (gen->cmd->cmd)
	{
		if (gen->cmd->in != 1)
			close(gen->cmd->in);
		if (check_exec(tab[0]) == 0)
			execve(tab[0], tab, env);
	}
}

int		ft_exec_phase_two(t_gen *gen, char **tab, char **env)
{
	pid_t	f;
	int		status;

	if (ft_redirection(gen) == 1)
		return (0);
	gen->f = 1;
	g_gen = gen;
	if ((f = fork()) == 0)
		ft_exec_phase_three(gen, tab, env);
	if (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	if (SIGSEGV == status)
		ft_putendl("Segfault");
	gen->status = status;
	if (gen->cmd->out != 1)
		close(gen->cmd->out);
	return (0);
}

void	exec_builtins(t_gen *gen, char **tab)
{
	int		save_in;
	int		save_out;

	save_in = dup(0);
	save_out = dup(1);
	if (ft_redirection(gen) == 1)
		return ;
	if (set_redirection(gen) == 1)
		return ;
	gen->f = 1;
	g_gen = gen;
	gen->status = ft_builtins(gen, tab);

	dup2(save_in, 0);
	dup2(save_out, 1);
	close(save_in);
	close(save_out);
}

int		ft_exec_phase_one(t_gen *gen, char **tab, char **env)
{
	if (check_builtins(tab[0]))
	{
		exec_builtins(gen, tab);
		return (0);
	}
	else if (tab[0] && (tab[0][0] == '.' || tab[0][0] == '/'))
	{
		if (check_exec(tab[0]))
			return (0);
	}
	else if ((tab[0] = check_cmd_path(gen, tab)) == NULL)
	{
		return (1);
	}
	return (ft_exec_phase_two(gen, tab, env));
}

void	open_file(t_cmd *cmd)
{
	t_cmd	*tmp;
	char	**split;
	int		fd;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->sym == 0 || tmp->sym == 1)
			break ;
		if (tmp->sym == 4 || tmp->sym == 3)
		{
			if (tmp->next)
			{
				split = ft_strsplit(tmp->next->cmd, ' ');
				fd = open(split[0], O_RDWR | O_APPEND | O_CREAT,
						S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
				close(fd);
				ft_freetab(split);
			}
		}
		tmp = tmp->next;
	}
}

void	ft_exec(t_gen *gen)
{
	char	**split;
	char	**env;
	char	*tmp;

	if (!gen->cmd)
		return ;
	ft_setterm(gen, 1);
	open_file(gen->cmd);
	while (gen->cmd)
	{
		env = ft_env_new_env(gen);
		split = ft_exec_split(gen->cmd->cmd);
		if (!split || !split[0])
			;
		else
		{
			split = ft_check_alias(gen, split);
			tmp = ft_strdup(split[0]);
			if (gen->cmd->prev && (gen->cmd->prev->sym == 3 || gen->cmd->prev->sym
						== 4 || gen->cmd->prev->sym == 5
						|| gen->cmd->prev->sym == 6))
			{
				if (gen->cmd->in != 1)
				{
					if (gen->cmd->prev && (gen->cmd->prev->sym == 3 || gen->cmd->prev->sym == 4))
					{
						ft_freetab(split);
						split = ft_strsplit(gen->cmd->cmd, ' ');
						add_file(gen, split);
					}
				}
				ft_check_file(gen, split);
			}
			else if (ft_exec_phase_one(gen, split, env))
				ft_not_found(gen, tmp);
			free(tmp);
			ft_etou(gen);
		}
		ft_freetab(env);
		gen->cmd = gen->cmd->next;
	}
	ft_setterm(gen, 0);
}
