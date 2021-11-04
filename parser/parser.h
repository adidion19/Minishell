/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:53:08 by artmende          #+#    #+#             */
/*   Updated: 2021/11/04 14:51:55 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_pipe_list
{
	char				**cmd_args;
	int					input;
	int					output;
	struct s_pipe_list	*next;
}	t_pipe_list;

typedef struct s_quote_state
{
	int	simple_quote;
	int	double_quote;
	int	global_quote;
}	t_quote_state;


void	*ft_memset(void *ptr, int c, unsigned int size);

/* typedef struct s_instruction
{
	int	nbr_of_section;
	
}	t_instruction;

typedef struct s_parsed_line
{
	int	nbr_of_instructions;
}	t_parsed_line; */

#endif
