/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:53:08 by artmende          #+#    #+#             */
/*   Updated: 2021/11/04 18:15:23 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_pipe_list
{
	char				**cmd_args;
	char				*input_str;
	char				*output_str;
	int					input_fd;
	int					output_fd;
	struct s_pipe_list	*next;
}	t_pipe_list;

typedef struct s_quote_state
{
	int	simple_quote;
	int	double_quote;
	int	global_quote;
}	t_quote_state;


void	*ft_memset(void *ptr, int c, size_t size);
void	*ft_calloc(size_t nmemb);

/* typedef struct s_instruction
{
	int	nbr_of_section;
	
}	t_instruction;

typedef struct s_parsed_line
{
	int	nbr_of_instructions;
}	t_parsed_line; */

#endif
