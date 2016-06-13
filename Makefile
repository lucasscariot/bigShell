# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lscariot <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/22 09:44:59 by lscariot          #+#    #+#              #
#*   Updated: 2016/06/13 18:40:06 by jhezard          ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME	= 42sh

CC		= clang

S_DIR	=

O_DIR	=

I_DIR	=

FLAGS	= -O3 -g -Wall -Wextra -Werror $(I_DIR) $(LIBS_DIR)

FILES	= main.c \

LIBS_F	= ./libft/libft.a

SRC		= $(addprefix $(S_DIR),$(FILES))

OBJS	= $(addprefix $(O_DIR),$(FILES:.c=.o))

LIBS	= $(addprefix -L. -l,$(LIBS_F))

RM		= rm -f

all: 		$(NAME)

$(NAME):
	@make -C src -j8

clean:
	@make -C src clean

fclean: 	clean
	@make -C src fclean

re:			fclean all

.PHONY: re clean fclean all
