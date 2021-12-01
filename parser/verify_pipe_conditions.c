/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_pipe_conditions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:45:17 by artmende          #+#    #+#             */
/*   Updated: 2021/12/01 16:16:45 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

/*
	verify_pipe_conditions:

	We cannot have 2 pipe symbols following each other with nothing in between.
	We cannot have a pipe symbol with nothing before it.
	We cannot have a pipe symbol followed by nothing.

	That means we need to have something before AND after each unquoted pipe
	symbol.
*/

int	verify_pipe_conditions(char *line)
{
	t_quote_state	quote;
	char			*last_pipe_symbol;

	if (*line == '|')
		return (display_syntax_error(*line));
	last_pipe_symbol = line;
	ft_memset(&quote, 0, sizeof(quote));
	while (*line)
	{
		update_quote_state(line, &quote);
		if (*line == '|' && quote.global_quote == 0)
		{
			if (*last_pipe_symbol == '|')
				last_pipe_symbol++;
			if (have_only_spaces(last_pipe_symbol, line - 1)
				|| have_only_spaces(line + 1, 0))
			{
				return (display_syntax_error(*line));
			}
			last_pipe_symbol = line;
		}
		line++;
	}
	return (1);
}

/*
	have_only_spaces:

	Checks that the string "from" only contains white spaces (or nothing).

	"from" has to be non null.
	If "to" is non null and superior/equal than "from", we check between
	"from" and "to", including themselves.

	If "to" is null, we check until the end of the string.
*/

int	have_only_spaces(char *from, char *to)
{
	if (!from)
		return (0);
	if (to && to >= from) //////////////
	{
		while (from <= to)
		{
			if (!ft_isspace(*from))
				return (0);
			from++;
		}
	}
	if (!to)
	{
		while (*from)
		{
			if (!ft_isspace(*from))
				return (0);
			from++;
		}
	}
	return (1);
}
