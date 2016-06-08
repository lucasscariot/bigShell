/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 12:12:00 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/02 14:46:38 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	check_split_quote(char *ch, char c)
{
	if (*ch == '\0')
	{
		if (c == '"')
			*ch = c;
		else if (c == '\'')
			*ch = c;
	}
	else
	{
		if (*ch == c)
			*ch = '\0';
	}
}

char	*ft_splitchar_one(char *str, char *new, char c)
{
	int			i;
	int			j;
	static char	ch = '\0';

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ch == '\0')
		{
			if (str[i] != c && str[i] != '\\' && str[i] != '\0')
			{
				new[j] = str[i];
				j++;
			}
			else if (str[i] != '\0')
			{
				new[j] = ' ';
				j++;
			}
		}
		else
		{
			new[j] = str[i];
			j++;
		}
		check_split_quote(&ch, str[i]);
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	*ft_splitchar(char *str, char c)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	return (ft_splitchar_one(str, new, c));
}
