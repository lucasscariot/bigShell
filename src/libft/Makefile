# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lscariot <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/26 07:58:18 by lscariot          #+#    #+#              #
#    Updated: 2016/06/02 12:28:49 by hfrely           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libft.a

SRCS 	= ft_atoi.c			ft_bzero.c		ft_memcpy.c		ft_memccpy.c	\
		  ft_memmove.c		ft_memchr.c		ft_strlen.c		ft_strdup.c		\
		  ft_strcpy.c		ft_strncpy.c	ft_strcat.c		ft_strncat.c	\
		  ft_strlcat.c		ft_strchr.c		ft_strrchr.c	ft_strstr.c		\
		  ft_strnstr.c		ft_strcmp.c		ft_strncmp.c	ft_atoi.c		\
		  ft_isalpha.c		ft_isdigit.c	ft_isalnum.c	ft_isascii.c	\
		  ft_isprint.c		ft_toupper.c	ft_tolower.c	ft_memalloc.c	\
		  ft_memdel.c		ft_strnew.c		ft_strdel.c		ft_strclr.c		\
		  ft_striter.c		ft_striteri.c	ft_strmap.c		ft_strmapi.c	\
		  ft_strequ.c		ft_strnequ.c	ft_strsub.c		ft_strjoin.c	\
		  ft_strtrim.c		ft_itoa.c		ft_putchar.c	ft_putstr.c		\
		  ft_putendl.c		ft_putnbr.c		ft_putchar_fd.c	ft_putstr_fd.c	\
		  ft_putendl_fd.c	ft_putnbr_fd.c	ft_memcmp.c		ft_memset.c		\
		  ft_strsplit.c		ft_lstadd.c		ft_lstiter.c	ft_lstdel.c		\
		  ft_lstdelone.c	ft_lstnew.c		get_next_line.c	ft_intlen.c		\
		  ft_strswap.c		ft_putcolor.c	ft_putnchar.c	ft_strndup.c	\
		  ft_strsplit_mc.c	ft_delchar.c	ft_addchar.c	ft_tablen.c		\
		  ft_freetab.c		ft_strreplace.c	ft_splitchar.c

DIRSRC	= $(addprefix ./ ,$(SRCS))

OBJS	= ${SRCS:%.c=.obj/%.o}

INC		= ../includes

FLAGS	= -Wall -Wextra -Werror -g

CC		= clang

AR		= ar rc

RANLIB	= ranlib

all: $(NAME)

$(NAME): $(OBJS)
	@echo ""
	@$(AR) $(NAME) $(OBJS)
	@$(RANLIB) $(NAME)
	@echo "\033[32mlibft created.\033[0m"

.obj/%.o: %.c
	@mkdir -p .obj
	@$(CC) -c $< -o $@ $(FLAGS) -I $(INC)
	@echo "\033[33m.\033[0m\c"

clean:
	@rm -rf .obj

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31mlibft cleaned.\033[0m"

re: fclean all

