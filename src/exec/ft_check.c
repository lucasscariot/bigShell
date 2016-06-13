/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 21:06:07 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/13 20:47:28 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	add_file(t_gen *gen, char **split)
{
	int		new_fd;
	int		ret;
	char	buff[1024];

	new_fd = open(split[0], O_RDWR | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	while ((ret = read(gen->cmd->in, buff, 1024 - 1)) > 0)
	{
		buff[ret] = '\0';
		ft_putstr_fd(buff, new_fd);
	}
	close(new_fd);
}

void	input_file(t_gen *gen, int ipipe[2], char **split)
{
	(void)gen;
	if (ft_read(split[0], ipipe[1]) == 1)
	{
		ft_putstr("Error\n");
	}
}

void	ft_check_file(t_gen *gen, char **split)
{
	int		ipipe[2];

	if (pipe(ipipe) == -1)
		return ;
	input_file(gen, ipipe, split);
	if (gen->cmd->next)
		gen->cmd->next->in = ipipe[0];
	if (close(ipipe[1]) == -1)
		return ;
	return ;
}

int		check_exec(char *str)
{
	struct stat	buf;

	if (stat(str, &buf) == -1)
		return (1);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	if (access(str, X_OK) == 0)
		return (0);
	else if (access(str, F_OK) == 0)
	{
		ft_putstr(str);
		ft_putstr(": permission denied\n");
	}
	return (1);
}

int		check_builtins(char *str)
{
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "setenv") == 0)
		return (1);
	else if (ft_strcmp(str, "unsetenv") == 0)
		return (1);
	else if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "history") == 0)
		return (1);
	else if (ft_strcmp(str, "alias") == 0)
		return (1);
	else if (ft_strcmp(str, "setalias") == 0)
		return (1);
	else if (ft_strcmp(str, "source") == 0)
		return (1);
	else
	{
		return (0);
	}
	return (1);
}
