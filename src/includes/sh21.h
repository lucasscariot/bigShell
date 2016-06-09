/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splace <splace@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 12:49:52 by hfrely            #+#    #+#             */
/*   Updated: 2016/06/09 15:12:14 by lscariot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>
# include <termcap.h>
# include <term.h>
# include <curses.h>
# include <string.h>
# include <dirent.h>
# include "libft.h"
# undef tab
# define SH "42sh"

typedef struct			s_cmd
{
	int					sym;
	char				*cmd;
	int					in;
	int					out;
	int					aggr;
	int					aggr_one;
	int					aggr_tow;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct			s_caps
{
	char				*line;
	int					cursor;
	int					len;
	int					row;
	int					stop;
	int					cut1;
	int					cut2;
	struct s_caps		*next;
	struct s_caps		*prev;
}						t_caps;

typedef struct			s_env
{
	char				*name;
	char				*content;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct			s_alias
{
	char				*cmd;
	char				*replace;
	struct s_alias		*next;
	struct s_alias		*prev;
}						t_alias;

typedef struct			s_gen
{
	int					aggr;
	int					aggr_one;
	char				*tmp_tab;
	int					stop;
	int					prompt_len;
	char				*prompt;
	char				*copy;
	int					fd;
	int					status;
	int					ctrlc;
	int					f;
	struct termios		term;
	struct termios		term_ori;
	t_env				*env;
	t_caps				*tcaps;
	t_cmd				*cmd;
	t_alias				*alias;
}						t_gen;

typedef struct			s_norm
{
	int					nb;
	char				*tmp;
	char				*tmp2;
	char				*str;
	DIR					*dir;
}						t_norm;

t_gen					*g_gen;

enum					e_key
{
	ENTER_KEY,
	UP_KEY,
	DOWN_KEY,
	LEFT_KEY,
	RIGHT_KEY,
	DEL_KEY,
	HOME_KEY,
	END_KEY,
	TAB_KEY,
	LEFT_ALT_KEY,
	RIGHT_ALT_KEY,
	UP_ALT_KEY,
	DOWN_ALT_KEY,
	ALT_Z,
	ALT_C,
	ALT_X,
	ALT_V,
	CTRL_L,
	CTRL_D,
	BASIC_KEY
};

int						ft_cmd_source(char *str);

char					*ft_init_key(int a, int b, int c, int d);
typedef void			t_exec(t_gen *gen, char *buf);
void					exec_enter(t_gen *gen, char *buf);
void					exec_up(t_gen *gen, char *buf);
void					exec_down(t_gen *gen, char *buf);
void					exec_left(t_gen *gen, char *buf);
void					exec_right(t_gen *gen, char *buf);
void					exec_del(t_gen *gen, char *buf);
void					exec_home(t_gen *gen, char *buf);
void					exec_end(t_gen *gen, char *buf);
void					exec_tab(t_gen *gen, char *buf);
void					exec_left_alt(t_gen *gen, char *buf);
void					exec_right_alt(t_gen *gen, char *buf);
void					exec_up_alt(t_gen *gen, char *buf);
void					exec_down_alt(t_gen *gen, char *buf);
void					exec_z_alt(t_gen *gen, char *buf);
void					exec_c_alt(t_gen *gen, char *buf);
void					exec_x_alt(t_gen *gen, char *buf);
void					exec_v_alt(t_gen *gen, char *buf);
void					exec_write(t_gen *gen, char *buf);
void					exec_ctrl_l(t_gen *gen, char *buf);
void					exec_ctrl_d(t_gen *gen, char *buf);
void					exec_clean(t_gen *gen);
void					exec_del_clean(t_gen *gen);
void					ft_point_slash(t_gen *gen, char *str, int nb);
int						ft_exec_quote(char c, int reset);
int						check_redi_exec(t_gen *gen, char *str);

void					ft_add_tcaps(t_gen *gen, char *buf);
t_caps					*ft_create_caps(t_caps *tcaps);
int						ft_term_count_cursor(t_gen *gen);
int						ft_term_count_row(t_gen *gen);
void					ft_refresh(t_gen *gen);
void					ft_select_right(t_gen *gen);
void					ft_select_left(t_gen *gen);
void					ft_delstrsub(t_gen *gen);
void					sig_sigquit(int sig);

int						ft_can(t_gen *gen);
void					ft_read_line(char **line, t_gen *gen);
void					ft_cmd_split(t_gen *gen, char *line);
t_cmd					*ft_create_list(t_cmd *list, char *cmd,
		int symb, int a[2]);
t_env					*ft_env_list(t_env *env, char *name, char *content);
char					*ft_slash(char *str);
char					*ft_after_slash(char *str);
void					ft_term_add_tab(t_gen *gen, t_norm *norm);

int						ft_prompt(t_gen *gen);
void					ft_update_prompt(t_gen *gen);
void					ft_exec_key(char *buf, t_gen *gen);
t_env					*ft_save_env(char **env);
void					ft_cpy_list(t_gen *gen);
int						ft_term_tab(t_gen *gen);
char					*ft_getenv(t_gen *gen, char *str);
void					ft_modenv(t_gen *gen, char *name, char *content);
void					ft_check_env(t_gen *gen);
void					ft_aff_line(t_gen *gen);

typedef int				t_builtins(t_gen *gen, char **tab);
int						ft_builtins(t_gen *gen, char **tab);
int						ft_exit(t_gen *gen, char **tab);
int						ft_cd(t_gen *gen, char **tab);
int						ft_echo(t_gen *gen, char **tab);
int						ft_env(t_gen *gen, char **tab);
int						ft_setenv(t_gen *gen, char **tab);
int						ft_unsetenv(t_gen *gen, char **tab);
int						ft_clear(t_gen *gen, char **tab);
int						ft_history(t_gen *gen, char **tab);
int						ft_alias(t_gen *gen, char **tab);
int						ft_source(t_gen *gen, char **tab);
int						ft_setalias(t_gen *gen, char **tab);
char					**ft_env_new_env(t_env *env);
char					**ft_env_new_tab(char **tab);
char					*ft_com_ok(char *str, char *str2);
int						ft_exec_phase_one(t_gen *gen, char **tab, char **env);

void					ft_exec(t_gen *gen);
int						ft_execute(t_gen *gen, char **tab);
void					ft_check_aggr(t_gen *gen);
int						get_output(t_gen *gen);
char					**ft_exec_split(char *str);
char					*ft_addchar_back(char *str, char fuck);
int						check_builtins(char *str);
int						check_exec(char *str);
int						ft_redirection(t_gen *gen);
char					*check_cmd_path(t_gen *gen, char **tab);
int						set_redirection(t_gen *gen);
int						ft_etou(t_gen *gen);
int						set_aggr(t_gen *gen);

int						ft_check_quote_cmd(char b, char a);
int						ft_check_select(char *line, int i);
void					ft_cmd_un(t_gen *gen, char **tmp, int nb, int *i);
int						ft_check_select_bis(char *line, int i);
int						ft_check_select_tow(char *line, int i);

char					**ft_check_alias(t_gen *gen, char **tab);
t_alias					*ft_create_alias(t_alias *alias,
		char *cmd, char *replace);
void					ft_check_file(t_gen *gen, char **split);
int						ft_read(char *file, int fd);
void					add_file(t_gen *gen, char **split);

#endif
