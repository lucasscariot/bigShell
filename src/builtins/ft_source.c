/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_source.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 15:15:04 by lscariot          #+#    #+#             */
/*   Updated: 2016/06/02 15:07:51 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	ft_source_un(t_gen *gen, char *tmp, int fd)
{
	while (get_next_line(fd, &tmp))
	{
		if (tmp[0] == '#' || tmp[0] == '\0' || tmp[0] == '\n')
		{
			if (tmp[1] == '#' && tmp[0] == '#')
				ft_putendl(ft_strtrim(&tmp[2]));
			free(tmp);
			continue ;
		}
		ft_cmd_split(gen, tmp);
		ft_exec(gen);
		free(tmp);
	}
}

int		ft_source(t_gen *gen, char **tab)
{
	char	*path;
	char	*tmp;
	int		fd;

	(void)tab;
	path = ft_getenv(gen, "HOME=");
	if (!path)
		return (1);
	tmp = ft_strjoin(path, "/.21rc");
	fd = open(tmp, O_RDONLY);
	if (fd == -1)
		return (1);
	free(path);
	free(tmp);
	ft_source_un(gen, tmp, fd);
	close(fd);
	return (0);
}
