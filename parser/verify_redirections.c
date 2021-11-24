/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:12:58 by artmende          #+#    #+#             */
/*   Updated: 2021/11/24 16:22:10 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

/*
	verify_redirections :

	We have to check that there are no syntax error with redirection, before
	we divide in pipe sections etc.

	Possible syntax error :
	- redirection symbol followed by nothing
	- redirection symbol followed by pipe symbol
	- redirection symbol followed by another redirection symbol
	- more than 2 redirection symbols together
	- mixed type redirection symbols

	We only consider unquoted redirection symbol here.
*/

int	have_something_before_pipe(char *str)
{
	// also check that it is not followed by another redirection symbol
	while (*str && !(*str == '|' || *str == '<' || *str == '>'))
	{
		if (!ft_isspace(*str))
			return (1);
		str++;
	}
	return (0);
}


int	verify_redirections(char *line)
{
	char			c;
	t_quote_state	quote;

	ft_memset(&quote, 0, sizeof(quote));
	while (line && *line)
	{
		update_quote_state(line, &quote);
		if (quote.global_quote == 0 && (*line == '>' || *line == '<'))
		{
			c = *line;
			if ((*(line + 1) == '>' || *(line + 1) == '<') && *(line + 1) != c) // no mixed type
				return (display_syntax_error(*line));
			if ((*(line + 1) == '>' || *(line + 1) == '<')
				&& !have_something_before_pipe(line + 2)) // check also for more than 2 of them
				return (display_syntax_error(*line));
			if (*(line + 1) != '>' && *(line + 1) != '<'
				&& !have_something_before_pipe(line + 1))
				return (display_syntax_error(*line));
		}
		line++;
	}
	return (1);
}
