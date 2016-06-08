/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscariot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 16:50:16 by lscariot          #+#    #+#             */
/*   Updated: 2016/06/02 13:06:59 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	ft_del_quote(char **av)
{
	int			i;
	int			j;
	char		*string;

	i = 0;
	while (av[i])
	{
		j = 0;
		if (ft_strchr(av[i], '"') || ft_strchr(av[i], '\''))
		{
			string = ft_strdup(av[i]);
			string[ft_strlen(string) - 1] = '\0';
			string++;
			av[i] = ft_strdup(string);
			string--;
			free(string);
		}
		while (av[i][j])
		{
			if (av[i][j] == '\\' && ft_strchr("\"'`", av[i][j + 1]))
				av[i][j] = 26;
			j++;
		}
		i++;
	}
}

void	ft_instring(char *quote, char c, int d)
{
	if (*quote == '\0' && ft_strchr("\"'", c))
		*quote = c;
	else if (*quote == c && d != '\\')
		*quote = '\0';
}

char	*ft_ndup(char *s)
{
	int			size;
	char		*new;
	int			i;
	char		qt;

	qt = '\0';
	i = 0;
	size = 0;
	ft_instring(&qt, *(s + i), *(s + i - 1));
	while ((*(s + i) != ' ' || qt != '\0')
			&& *(s + i) != '\0' && size++ >= 0 && i++ >= 0)
		ft_instring(&qt, *(s + i), *(s + i - 1));
	new = (char*)malloc(sizeof(*new) * size + 1);
	i = 0;
	qt = '\0';
	ft_instring(&qt, *(s + i), *(s + i - 1));
	while ((*(s + i) != ' ' || qt != '\0') && *(s + i) != '\0')
	{
		new[i] = *(s + i);
		i++;
		ft_instring(&qt, *(s + i), *(s + i - 1));
	}
	new[i] = '\0';
	return (new);
}

int		ft_line_nbr(char *str)
{
	int			count;
	char		quote;
	int			i;

	count = 0;
	quote = '\0';
	i = 0;
	while (str[i])
	{
		ft_instring(&quote, str[i], str[i - 1]);
		while (str[i] == ' ')
		{
			i++;
			ft_instring(&quote, str[i], str[i - 1]);
		}
		if (str[i] == '\0')
			return (count);
		count++;
		while ((str[i] != ' ' || quote) != '\0' && str[i] != '\0')
		{
			i++;
			ft_instring(&quote, str[i], str[i - 1]);
		}
	}
	return (count);
}

char	**ft_exec_split(char *str)
{
	char		**tab;
	int			i;
	int			l;
	char		quote;

	quote = '\0';
	i = 0;
	l = ft_line_nbr(str);
	tab = (char**)malloc(sizeof(*tab) * (l + 1));
	tab[l] = NULL;
	while (i < l)
	{
		while (*str == ' ')
			str++;
		ft_instring(&quote, *str, *(str - 1));
		tab[i] = ft_ndup(str);
		while ((*str != ' ' || quote != '\0') && *str != '\0')
		{
			str++;
			ft_instring(&quote, *str, *(str - 1));
		}
		i++;
	}
	ft_del_quote(tab);
	return (tab);
}
