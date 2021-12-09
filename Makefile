# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adidion <adidion@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 16:20:02 by ybrutout          #+#    #+#              #
#    Updated: 2021/12/09 11:44:33 by adidion          ###   ########.fr        #
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
		command/export_no_arg_2.c\
		command/ft_env_check_arg.c\
		redirections/ft_open.c\
		redirections/ft_heredoc.c\
		pipes/ft_pick_pipe.c\
		pipes/ft_verify_redi.c\
		pipes/ft_multiple_pipe.c\
		error/error.c\
		utils/utils.c\
		utils/utils_b.c\
		utils/utils_c.c\
		utils/utils_d.c\
		utils/utils_e.c\
		utils/utils_f.c\
		utils/utils_g.c\
		utils/ft_atoi.c\
		utils/ft_itoa.c\
		utils/ft_split.c\
		init_env.c\
		parser/add_input_output_to_cmd_node.c\
		parser/add_pipe_section.c\
		parser/display_error.c\
		parser/dollar_variables_handling.c\
		parser/get_input_output.c\
		parser/parser.c\
		parser/parser_utils.c\
		parser/parsing_debug_functions.c\
		parser/update_quote_state.c\
		parser/verify_pipe_conditions.c\
		parser/verify_redirections.c\
		parser/words_list_1.c\
		parser/words_list_2.c\
		signal/signal.c\
		signal/signal_2.c\

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