/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:12:58 by artmende          #+#    #+#             */
/*   Updated: 2021/12/08 16:48:36 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

/*
	verify_redirections :

	We have to check that there are no syntax error with redirection, before
	we divide in pipe sections etc.

	Possible syntax error :
	- redirection symbol followed by nothing.
	- redirection symbol followed by pipe symbol.
	- redirection symbol followed by another redirection symbol.
	- more than 2 redirection symbols together.
	- mixed type redirection symbols.

	We only consider unquoted redirection symbol here.
*/

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
			if ((*(line + 1) == '>' || *(line + 1) == '<') && *(line + 1) != c)
				return (display_syntax_error(*line));
			if ((*(line + 1) == '>' || *(line + 1) == '<')
				&& !have_something_before_pipe(line + 2))
				return (display_syntax_error(*line));
			if (*(line + 1) != '>' && *(line + 1) != '<'
				&& !have_something_before_pipe(line + 1))
				return (display_syntax_error(*line));
		}
		line++;
	}
	return (1);
}

int	have_something_before_pipe(char *str)
{
	while (*str && !(*str == '|' || *str == '<' || *str == '>'))
	{
		if (!ft_isspace(*str))
			return (1);
		str++;
	}
	return (0);
}

/*
	verify_redir_var :

	When display_ambiguous_redirect is called, it puts
	cmd_node->delete_this_node to 1. That will stop the parsing of that pipe
	section. The command associated with that pipe section is not executed.
*/

int	verify_redir_var(t_lst_cmd *cmd_node, char *word, char **env)
{
	int				i;
	char			*var_name;
	char			*var_content;
	t_quote_state	quote;

	ft_memset(&quote, 0, sizeof(quote));
	i = 0;
	while (word && word[i] && update_quote_state(&word[i], &quote))
	{
		if (word[i] == '$' && quote.global_quote == 0 && word[i + 1]
			&& !ft_isspace(word[i + 1]))
		{
			var_name = get_var_name(&word[i]);
			var_content = get_var_content(var_name, (t_quote_state){0, 1, 1},
					env);
			if (!redir_var_conditions(i, word, var_name, var_content))
				display_ambiguous_redirect(cmd_node, var_name);
			i += ft_strlen(var_name);
			free(var_name);
			free(var_content);
		}
		if (++i && cmd_node->delete_this_node == 1)
			return (0);
	}
	return (1);
}

/*
	redir_var_conditions :

	When a redirection is an unquoted environment variable, the following cases
	will produce an ambiguous redirect error.

	Possible errors :
	unquoted var that contains more than one word.
	unquoted var that starts with spaces and var is preceded by something.
	unquoted var that finishes with spaces and is followed by something.
*/

int	redir_var_conditions(int i, char *word, char *var_name, char *var_content)
{
	if (str_have_more_than_one_word(var_content)
		|| (i && str_starts_with_space(var_content))
		|| (word[i + ft_strlen(var_name) + 1]
			&& str_ends_with_space(var_content)))
	{
		return (0);
	}
	else
		return (1);
}
