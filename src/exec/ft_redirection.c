/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 22:04:42 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/02 17:58:04 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		ft_read(char *file, int fd)
{
	int		new_fd;
	int		ret;
	char	buff[1024];

	if ((new_fd = open(file, O_RDONLY)) == -1)
		return (1);
	while ((ret = read(new_fd, buff, 1024 - 1)) > 0)
	{
		buff[ret] = '\0';
		if (write(fd, buff, ret) != ret)
			return (1);
	}
	close(new_fd);
	return (0);
}

void	ft_input_un(char **tab, int pipe)
{
	int		i;

	i = 1;
	while (tab[i])
	{
		if (!tab[i + 1])
			break ;
		ft_putstr_fd(tab[i], pipe);
		ft_putchar_fd('\n', pipe);
		i++;
	}
}

int		ft_input(t_gen *gen, int ipipe[2])
{
	char	**tab;

	if (gen->cmd->sym == 5 && gen->cmd->next && gen->cmd->next->cmd)
	{
		tab = ft_strsplit(gen->cmd->next->cmd, ' ');
		if (ft_read(tab[0], ipipe[1]) == 1)
		{
			ft_putstr("Error\n");
			ft_freetab(tab);
			return (1);
		}
		ft_freetab(tab);
	}
	else if (gen->cmd->sym == 6 && gen->cmd->next && gen->cmd->next->cmd)
	{
		tab = ft_strsplit(gen->cmd->next->cmd, '\n');
		ft_input_un(tab, ipipe[1]);
	}
	return (0);
}

int		get_input(t_gen *gen)
{
	int		ipipe[2];

	if (pipe(ipipe) == -1)
		return (1);
	ft_input(gen, ipipe);
	gen->cmd->in = ipipe[0];
	if (close(ipipe[1]) == -1)
		return (1);
	return (0);
}

int		ft_redirection(t_gen *gen)
{
	int		s;

	s = gen->cmd->sym;
	if ((s == 5 || s == 6) && get_input(gen) == 1)
		return (1);
	else if ((s == 3 || s == 4 || s == 2) && get_output(gen) == 1)
		return (1);
	return (0);
}
