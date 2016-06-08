/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lscariot@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 22:05:26 by lucas             #+#    #+#             */
/*   Updated: 2016/03/02 14:06:40 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		occ_test(char **occ, char *save)
{
	if (*occ != NULL)
	{
		**occ = '\0';
		*occ += 1;
		ft_strcpy(save, *occ);
		return (1);
	}
	else
		return (0);
}

static char		*dyn_alloc(char **line, int *ret)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(*line) + *ret + 1));
	if (str == NULL)
		return (NULL);
	str = ft_strcpy(str, *line);
	free(*line);
	return (str);
}

int				get_next_line(int const fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;
	static char	save[BUFF_SIZE] = "";
	char		*occ;

	*line = (char *)malloc(sizeof(char *) * (BUFF_SIZE + ft_strlen(save) + 1));
	*line = ft_strcpy(*line, save);
	while (((occ = ft_strchr(*line, '\n')) == NULL)
			&& ((ret = read(fd, buf, BUFF_SIZE)) > 0))
	{
		buf[ret] = '\0';
		if ((*line = dyn_alloc(line, &ret)) == NULL)
			return (-1);
		ft_strcat(*line, buf);
	}
	occ = ft_strchr(*line, '\n');
	if (occ_test(&occ, save) == 1)
		return (1);
	if (ret == 0)
		return (0);
	else
		return (-1);
}
