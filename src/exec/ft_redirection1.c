/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 19:29:14 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/02 17:25:26 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		set_aggr(t_gen *gen)
{
	if (gen->cmd->aggr)
		dup2(gen->cmd->aggr_one, gen->cmd->aggr_tow);
	return (0);
}

int		set_redirection(t_gen *gen)
{
	if (gen->cmd->out != 1)
	{
		if (gen->aggr)
			dup2(gen->cmd->out, gen->aggr_one);
		if (dup2(gen->cmd->out, 1) == -1)
			return (1);
		close(gen->cmd->out);
	}
	if (gen->cmd->in != 1)
	{
		if (dup2(gen->cmd->in, 0) == -1)
			return (1);
		close(gen->cmd->in);
	}
	return (0);
}

int		ft_pipe(t_gen *gen)
{
	int		ipipe[2];

	if (gen->cmd->next)
	{
		if (pipe(ipipe) == -1)
			return (1);
		gen->cmd->out = ipipe[1];
		gen->cmd->next->in = ipipe[0];
	}
	else
		return (1);
	return (0);
}

int		get_output(t_gen *gen)
{
	int		fd;
	char	**tab;

	if (gen->cmd->next->cmd)
		tab = ft_strsplit(gen->cmd->next->cmd, ' ');
	if (gen->cmd->sym == 3 && gen->cmd->next)
	{
		if ((fd = open(tab[0], O_WRONLY | O_TRUNC | O_CREAT,
						S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
			return (1);
		gen->cmd->out = fd;
	}
	else if (gen->cmd->sym == 4 && gen->cmd->next)
	{
		if ((fd = open(tab[0], O_RDWR | O_APPEND | O_CREAT,
						S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
			return (1);
		gen->cmd->out = fd;
	}
	else if (gen->cmd->sym == 2 && ft_pipe(gen) == 1)
		return (1);
	ft_freetab(tab);
	return (0);
}
