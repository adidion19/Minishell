# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adidion <adidion@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 16:20:02 by ybrutout          #+#    #+#              #
#    Updated: 2021/11/28 17:51:06 by adidion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I includes/

RPATH = /Users/$(USER)/.brew/opt/readline/

RL_FLAGS=	-L/usr/include  -lreadline\
			-L /Users/$(USER)/.brew/opt/readline/lib\
			-I/Users/$(USER)/.brew/opt/readline/include

SRC =	minishell.c\
		command/env.c\
		command/pwd.c\
		command/cd.c\
		command/echo.c\
		command/exit.c\
		command/export.c\
		command/other_command.c\
		command/ft_choose_command.c\
		command/ft_its_cd.c\
		command/ft_its_echo.c\
		command/ft_its_env.c\
		command/ft_its_exit.c\
		command/ft_its_export.c\
		command/ft_its_pwd.c\
		command/ft_its_unset.c\
		command/unset.c\
		command/export_no_arg.c\
		command/ft_env_check_arg.c\
		pipes/ft_one_pipe.c\
		pipes/ft_pick_pipe.c\
		pipes/ft_verify_redi.c\
		error/error.c\
		utils/utils.c\
		utils/utils_b.c\
		utils/utils_c.c\
		utils/utils_d.c\
		utils/ft_atoi.c\
		utils/ft_itoa.c\
		utils/ft_split.c\
		init_env.c\
		redirections/ft_open.c\
		signal/signal.c\
		#pipes/ft_multiple_pipe.c\#

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
