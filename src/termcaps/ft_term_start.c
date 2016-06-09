/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 18:07:09 by lscariot          #+#    #+#             */
/*   Updated: 2016/06/09 14:25:18 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	*ft_init_key(int a, int b, int c, int d)
{
	char	*key;

	if (!(key = (char *)malloc(sizeof(char) * 5)))
		return (NULL);
	ft_memset(key, 0, 5);
	key[0] = a;
	key[1] = b;
	key[2] = c;
	key[3] = d;
	key[4] = '\0';
	return (key);
}

void	ft_read_line(char **line, t_gen *gen)
{
	char	buf[4096];
	int		ret;

	(void)line;
	if (gen->tcaps == NULL || gen->tcaps->line[0] != 0)
		gen->tcaps = ft_create_caps(gen->tcaps);
	gen->stop = 1;
	gen->fd = open("/dev/tty", O_RDWR);
	while (gen->stop)
	{
		ft_bzero(buf, 4096);
		ret = read(gen->fd, buf, 4096);
		buf[ret] = '\0';
		ft_exec_key(buf, gen);
	}
	ft_putchar('\n');
	*line = ft_strdup(gen->tcaps->line);
	close(gen->fd);
}
