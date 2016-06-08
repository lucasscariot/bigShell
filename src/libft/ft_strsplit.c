/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <lscariot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 11:44:59 by lscariot          #+#    #+#             */
/*   Updated: 2016/02/06 22:58:48 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_cont(char const *s, char c)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			j++;
			i++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (j);
}

char	*ft_add(size_t *i, char const *s, char c)
{
	size_t		size;
	size_t		j;
	char		*str;

	size = *i;
	j = 0;
	while (s[size] && s[size] != c)
		size++;
	str = ft_strnew(size - *i);
	if (!str)
		return (NULL);
	while (*i < size)
	{
		str[j] = s[*i];
		j++;
		*i += 1;
	}
	return (str);
}

char	**ft_strsplit(char const *s, char c)
{
	char		**str;
	size_t		o;
	size_t		*i;
	size_t		j;

	o = 0;
	i = &o;
	j = 0;
	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (ft_cont(s, c) + 1));
	if (!str)
		return (0);
	while (j < ft_cont(s, c))
	{
		while (s[*i] == c)
			*i += 1;
		if (s[*i] != c && s[*i])
			str[j++] = ft_add(i, s, c);
	}
	str[j] = NULL;
	return (str);
}
