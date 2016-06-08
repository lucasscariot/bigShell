/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 15:20:59 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/01 16:53:04 by hfrely           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		ft_check_select_tow(char *line, int i)
{
	if (ft_isdigit(line[i]) && (line[i + 1] == '>'
			|| line[i + 1] == '<') && line[i + 2] == '&'
			&& (ft_isdigit(line[i + 3]) || line[i + 3] == '-'))
		return (9);
	else if (ft_isdigit(line[i]) && line[i + 1] == '<' && line[i + 2] == '&'
			&& ft_isdigit(line[i + 3]))
		return (10);
	else
		return (0);
}

int		ft_check_select_bis(char *line, int i)
{
	if (line[i] == '>' && line[i + 1] == '>'
			&& line[i - 1] != '>' && line[i + 2] != '>')
		return (4);
	else if (line[i] == '<' && line[i + 1] == '<'
			&& line[i + 2] != '<' && line[i - 1] != '<')
		return (6);
	else if (line[i] == '&' && line[i + 1] == '&')
		return (7);
	else if (line[i] == '|' && line[i + 1] == '|'
			&& line[i - 1] != '|' && line[i + 2] != '|')
		return (8);
	else
		return (0);
}

int		ft_check_select(char *line, int i)
{
	if (line[i] == ';' && line[i - 1] != ';' && line[i + 1] != ';')
		return (1);
	else if (line[i] == '|' && line[i + 1] != '|' && line[i - 1] != '|')
		return (2);
	else if (line[i] == '>' && line[i + 1] != '>' && line[i + 1] != '&'
			&& line[i - 1] != '>')
		return (3);
	else if (line[i] == '<' && line[i + 1] != '<' && line[i + 1] != '&'
			&& line[i + 1] != '<' && line[i - 1] != '<')
		return (5);
	else
		return (0);
}

int		ft_check_quote_cmd(char b, char a)
{
	static char ch = '\0';

	if (ch != '\0')
	{
		if (ch == a && b != '\\')
		{
			ch = '\0';
			return (0);
		}
		return (1);
	}
	if (a == '"' && b != '\\')
		ch = a;
	else if (a == '\'' && b != '\\')
		ch = a;
	if (ch == '\0')
		return (0);
	return (1);
}

void	ft_cmd_un(t_gen *gen, char **tmp, int nb, int *i)
{
	int		a[2];

	a[0] = 0;
	a[1] = 0;
	gen->cmd = ft_create_list(gen->cmd, *tmp, nb, a);
	free(*tmp);
	*tmp = ft_strnew(1);
	(*i)++;
}
