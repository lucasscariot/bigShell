/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_mc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 13:16:15 by hfrely            #+#    #+#             */
/*   Updated: 2016/04/26 16:49:50 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_count_ok(char s, const char *c)
{
	int		i;

	i = -1;
	while (c[++i])
	{
		if (s == c[i])
			return (1);
	}
	return (0);
}

static int		ft_strsepc(const char *s, const char *c)
{
	int			count;
	char		save;

	count = 0;
	save = '\0';
	while (*s != '\0')
	{
		if (ft_count_ok(*s, c))
			save = '\0';
		if (!ft_count_ok(*s, c) && save == '\0')
		{
			save = 'c';
			count++;
		}
		s++;
	}
	return (count);
}

char			**ft_strsplit_mc(char const *s, const char *c)
{
	char		**p_out;
	int			pos_s;
	int			pos1;
	int			pos2;
	char		*null_ptr;

	null_ptr = NULL;
	pos_s = 0;
	pos1 = 0;
	pos2 = 0;
	if (s == NULL)
		return (NULL);
	p_out = (char **)malloc(sizeof(char *) * (ft_strsepc(s, c) + 1));
	while (s[pos1] != '\0')
	{
		while (ft_count_ok(s[pos1], c))
			pos1++;
		pos2 = pos1;
		while (!ft_count_ok(s[pos1], c) && s[pos1] != '\0')
			pos1++;
		if (pos1 > pos2)
			p_out[pos_s++] = ft_strsub(s, pos2, (pos1 - pos2));
	}
	p_out[pos_s] = null_ptr;
	return (p_out);
}
