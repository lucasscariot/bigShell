/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrely <hfrely@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 13:45:04 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/13 20:48:33 by jhezard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	sig_sigint(int sig)
{
	if (sig == SIGINT && g_gen->f == 0)
	{
		ft_putchar('\n');
		g_gen->status = 1;
		free(g_gen->tcaps->line);
		g_gen->tcaps->line = ft_strnew(1);
		g_gen->tcaps->cursor = 0;
		g_gen->tcaps->len = 0;
		g_gen->tcaps->row = 0;
		ft_prompt(g_gen);
	}
	else
	{
		ft_putchar('\n');
	}
}

int		ft_check_line_empty(char *str)
{
	int		i;
	int		ok;

	i = 0;
	ok = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			ok = 1;
		i++;
	}
	return (ok);
}

char	*check_n(char *str)
{
	char	*line;

	line = ft_splitchar(str, '\n');
	free(str);
	return (line);
}

void	main_loop(t_gen gen, char *line)
{
	while (42)
	{
		gen.f = 0;
		g_gen = &gen;
		handle_all_signals();
		ft_update_prompt(&gen);
		ft_prompt(&gen);
		ft_read_line(&line, &gen);
		line = check_n(line);
		if (line[0] && ft_check_line_empty(line))
		{
			if (ft_cmd_source(line))
			{
				ft_source(&gen, NULL);
				continue ;
			}
			ft_cmd_split(&gen, line);
			ft_exec(&gen);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	char	*line;
	t_gen	gen;

	(void)ac;
	(void)av;
	signal(SIGTSTP, sig_sigquit);
	signal(SIGINT, sig_sigint);
	ft_can(&gen);
	gen.env = ft_save_env(env);
	ft_check_env(&gen);
	line = ft_strnew(2);
	gen.tcaps = NULL;
	gen.copy = NULL;
	gen.alias = NULL;
	gen.cmd = NULL;
	gen.prompt = NULL;
	ft_source(&gen, NULL);
	main_loop(gen, line);
	return (0);
}
