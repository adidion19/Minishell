# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adidion <adidion@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 16:20:02 by ybrutout          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2021/11/23 15:48:21 by adidion          ###   ########.fr        #
=======
#    Updated: 2021/11/23 15:25:11 by ybrutout         ###   ########.fr        #
>>>>>>> 1550219e35eca9d297372a32ebd724e8b32560cc
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I includes/

RPATH = /Users/$(USER)/.brew/opt/readline/

RL_FLAGS    =   -L/usr/include  -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include

SRC =	minishell.c\
		command/env.c\
		command/pwd.c\
		command/cd.c\
		command/echo.c\
		command/exit.c\
		command/export.c\
		command/unset.c\
		command/other_command.c\
		command/ft_choose_command.c\
		command/ft_its_cd.c\
		command/ft_its_echo.c\
		command/ft_its_env.c\
		command/ft_its_exit.c\
		command/ft_its_export.c\
		command/ft_its_pwd.c\
<<<<<<< HEAD
		command/its_unset\
=======
		command/ft_its_unset.c \
		command/unset.c \
>>>>>>> 1550219e35eca9d297372a32ebd724e8b32560cc
		utils/utils.c\
		utils/utils_b.c\
		utils/utils_c.c\
		utils/utils_d.c\
		error/error.c\
		utils/ft_atoi.c\
		utils/ft_itoa.c\
		utils/ft_split.c\
		init_env.c\
		redirections/ft_open.c\
		signal/signal.c \

OBJ = ${SRC:c=o}

%.o: %.c
	@${CC} ${CFLAGS} ${RFLAGS} -c $< -o $@

all : ${NAME}

${NAME}: ${OBJ}
	@${CC} ${CFLAGS} ${RL_FLAGS} -o ${NAME} ${OBJ}

clean :
	@rm -f ${OBJ}

fclean : clean
	@rm -f ${NAME}

allup: all clean

re: clean all
