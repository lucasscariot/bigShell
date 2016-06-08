/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_fnt3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 11:43:16 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/08 14:45:06 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		ft_exec_quote_bis(char ch, char c)
{
	if (ch == c)
		return (1);
	return (0);
}

int		ft_exec_quote(char c, int reset)
{
	static char	ch = '\0';

	if (reset)
	{
		ch = '\0';
		return (0);
	}
	if (ch != '\0')
	{
		if (ft_exec_quote_bis(ch, c))
		{
			ch = '\0';
			return (0);
		}
		return (1);
	}
	if (c == '\'')
		ch = c;
	else if (c == '"')
		ch = c;
	else if (c == '`')
		ch = c;
	if (ch == '\0')
		return (0);
	return (1);
}

void	check_redi_exec_deux(void)
{
	ft_putchar('\n');
	ft_putstr(SH);
	ft_putstr(": parse error");
}

int		check_redi_exec_un(t_gen *gen, char **split, int i)
{
	if (gen->cmd->prev && gen->cmd->prev->sym == 6)
	{
		split = ft_strsplit_mc(gen->cmd->cmd, " \n");
		i = ft_tablen(split);
		if (i == 0)
		{
			check_redi_exec_deux();
			gen->tcaps->line = ft_strdup("");
			return (0);
		}
		if (i >= 2)
		{
			if (ft_strcmp(split[0], split[i - 1]) == 0)
			{
				while (gen->cmd)
					gen->cmd = gen->cmd->next;
				return (0);
			}
			else
				return (1);
		}
		else
			return (1);
	}
	return (2);
}

int		check_redi_exec(t_gen *gen, char *str)
{
	char	**split;
	int		i;
	int		nb;

	while (gen->cmd)
		gen->cmd = gen->cmd->next;
	ft_cmd_split(gen, str);
	i = 0;
	split = NULL;
	while (gen->cmd)
	{
		if ((nb = check_redi_exec_un(gen, split, i)))
		{
			if (nb == 0)
				return (0);
			else if (nb == 1)
				return (1);
		}
		if (gen->cmd == NULL)
			break ;
		gen->cmd = gen->cmd->next;
	}
	return (0);
}
