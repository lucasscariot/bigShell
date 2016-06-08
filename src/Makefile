# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lscariot <lscariot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/22 09:44:59 by lscariot          #+#    #+#              #
#    Updated: 2016/06/08 18:27:41 by lscariot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= 42sh

LINK	= ../42sh

CC		= clang -g

S_DIR	=

O_DIR	=

I_DIR	=

FLAGS	=  -O3 -g -Wall -Wextra -Werror $(I_DIR) $(LIBS_DIR)

FILES	=	main.c							ft_prompt.c					\
			ft_env.c						ft_norme.c					\
			termcaps/ft_can.c											\
			termcaps/ft_term_start.c		termcaps/ft_term_fnt.c		\
			termcaps/ft_term_list.c			termcaps/ft_term_exec.c		\
			termcaps/ft_term_tab.c			ft_getenv.c					\
			parsing/ft_cmd.c				parsing/ft_list.c			\
			exec/ft_main.c					exec/ft_exec_split.c		\
			builtins/ft_main.c				builtins/ft_exit.c			\
			builtins/ft_cd.c				builtins/ft_echo.c			\
			builtins/ft_env.c				builtins/ft_setenv.c		\
			builtins/ft_unsetenv.c			builtins/ft_clear.c			\
			exec/ft_check.c					exec/ft_redirection.c		\
			exec/ft_etou.c					builtins/ft_history.c		\
			alias/ft_main.c					alias/ft_list.c				\
			builtins/ft_alias.c				builtins/ft_setalias.c		\
			builtins/ft_source.c			termcaps/ft_term_fnt1.c		\
			termcaps/ft_term_aff.c			termcaps/ft_term_fnt2.c		\
			exec/ft_redirection1.c										\
			parsing/ft_cmd1.c				ft_source.c					\
			termcaps/ft_term_tab1.c			termcaps/ft_term_tab2.c		\
			termcaps/ft_term_fnt3.c			termcaps/ft_term_fnt4.c		\
			termcaps/ft_term_fnt5.c			termcaps/ft_term_fnt6.c		\

LIBS_F	= ./libft/libft.a -lncurses

SRC		= $(addprefix $(S_DIR),$(FILES))

OBJS	= $(addprefix $(O_DIR),$(FILES:.c=.o))

LIBS	= $(addprefix -L. -l,$(LIBS_F))

RM		= rm -f

all: 		$(NAME)

$(NAME): 	$(OBJS)
	@echo ""
	@make -C libft
	@$(CC) $(FLAGS) -I./includes $(LIBS_F) $^ -o $(LINK)
	@echo "\033[32m$(NAME) created.\033[0m"

$(O_DIR)%.o:		$(S_DIR)%.c
	@$(CC) $(FLAGS) -I./includes -c $< -o $@
	@echo "\033[33m.\033[0m\c"

clean:
	@$(RM) $(OBJS)
	@make -C libft clean

fclean: 	clean
	@$(RM) $(LINK)
	@make -C libft fclean
	@echo "\033[31m$(NAME) cleaned.\033[0m"

re:			fclean all

.PHONY: re clean fclean all
