/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:07:27 by artmende          #+#    #+#             */
/*   Updated: 2021/11/04 17:44:54 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

void	update_quote_state(char c, t_quote_state *state)
{
	if (c == '\'')
	{
		if (state->global_quote == 0)
		{
			state->simple_quote = 1;
			state->global_quote = 1;
		}
		else if (state->simple_quote != 0)
			ft_memset(state, 0, sizeof(t_quote_state));
	}
	if (c == '"')
	{
		if (state->global_quote == 0)
		{
			state->double_quote = 1;
			state->global_quote = 1;
		}
		else if (state->double_quote != 0)
			ft_memset(state, 0, sizeof(t_quote_state));
	}
}

void	extract_input(t_pipe_list *node, char *from, char *to)
{
	
}

void	extract_output(t_pipe_list *node, char *from, char *to)
{

}

void	extract_string_array(t_pipe_list *node, char *from, char *to)
{
	
}

t_pipe_list	*add_pipe_section(t_pipe_list *list, char *from, char *to)
{
	t_pipe_list	*ret;
	t_pipe_list	*temp;

	ret = malloc(sizeof(t_pipe_list));
	if (!ret)
		return (NULL);
	extract_input(ret, from, to);
	extract_output(ret, from, to);
	extract_string_array(ret, from, to);
	ret->next = 0;
	if (!list)
		return (ret);
	temp = list;
	while (temp && temp->next)
		temp = temp->next;
	// temp points now to the last element of the list
	temp->next = ret;
	return (list);
}

t_pipe_list	*parser(char *line)
{
	t_pipe_list		*ret;
	t_quote_state	quote;
	char			*cursor;

	if (!line)
		return (NULL);
	ft_memset(&quote, 0, sizeof(quote));
	ret = 0;
	cursor = line;
	while (*line)
	{
		// we keep browsing as long as we didnt find a | outside of quote
		// if we are in quote, we just browse
		// if we are not in quote, we look for |
		while (*cursor)
		{
			update_quote_state(*cursor, &quote);
			if (*cursor == '|' && quote.global_quote == 0)
				break ;
			cursor++;
		}
		// here cursor points to the end of the section. can be a pipe or the end of the line
		ret = add_pipe_section(ret, line, cursor);
		if (*cursor) // if cursor is on a pipe symbol, we go to the next char for the next loop, otherwise we stay at 0 and we exit the loop
			cursor++;
		line = cursor;
	}
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{

	
	int	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	if (argc > 1)
	{
		printf("\n%s\n\n", argv[1]);
		parser(argv[1]);
	}
	return (0);
}
