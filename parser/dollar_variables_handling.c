/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_variables_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:36:46 by artmende          #+#    #+#             */
/*   Updated: 2021/11/27 17:57:17 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

char	*get_var_content(char *var_name, t_quote_state quote)
{
	char	*raw_value;

	raw_value = getenv(var_name);
	if (ft_strlen(raw_value) == 0)
		return (ft_strdup(""));
	if (quote.double_quote)
		return (ft_strdup(raw_value));
	else
		return (ft_strtrim(raw_value, "\t\n\r\v\f "));
		// need to protect return values ?
}

char	*get_var_name(char *str)
{
	char	*cursor;

	str++;
	cursor = str;
	while (*cursor)
	{
		if (*cursor == '\'' || *cursor == '"' || ft_isspace(*cursor))
			break ;
		cursor++;
	}
	return (duplicate_part_of_str(str, cursor - 1));
}

// rewrite this function with same structure as verify_redir_var
char	*expand_variables_in_single_word(char *word)
{ // no need to free original word
	// go until the first unquoted dollar
	// str join all until there
	// find the end of variable name
	// str join what was before with getenv var
	// go until the next unquoted dollar
	// etc etc
	// don't forget to free each time

	int				i;
	char			*ret;
	char			*var_name;
	char			*var_content;
	t_quote_state	quote;
	
	ft_memset(&quote, 0, sizeof(quote));
	ret = 0;
	i = 0;
	while (word && word[i])
	{
		i = 0;
		while (word[i] && !(word[i] == '$' && quote.simple_quote == 0 && word[i + 1] && !ft_isspace(word[i + 1]))) // browse until we find a $ to expand
		{
			(void)(update_quote_state(&word[i], &quote) && i++);
//			i++;
		} // i is the number of char to copy
		ret = malagain(ret, word, i); // we add i char from word to ret
		if (word[i] == 0)
			break ;
		var_name = get_var_name(&word[i]); // what happens if word[i] == 0 ?
		var_content = get_var_content(var_name, quote);
		ret = malagain(ret, var_content, ft_strlen(var_content)); // if the variable doesnt exist, getenv is null pointer
		word = &word[i] + ft_strlen(var_name) + 1; // we go directly to after the variable name. we start from the $ (&word[i]) and we add the length of var + 1 (for the $)
		free(var_name);
		free(var_content);
	}
	return (ret);
}

//	possible errors :
//	unquoted var that contains more than one word
//	unquoted var that starts with spaces and var is preceded by something
//	unquoted var that finishes with spaces and is followed by something





int	verify_redir_var(t_lst_cmd *cmd_node, char *word)
{
	int				i;
	char			*var_name;
	char			*var_content;
	t_quote_state	quote;

	ft_memset(&quote, 0, sizeof(quote));
	i = 0;
	while (word && word[i])
	{
		update_quote_state(&word[i], &quote);
		if (word[i] == '$' && quote.global_quote == 0 && word[i + 1] && !ft_isspace(word[i + 1]))
		{
			var_name = get_var_name(&word[i]);
			var_content = get_var_content(var_name, (t_quote_state){0, 1, 1}); // take it as if it was in double quote, so we have the spaces too
			if (str_have_more_than_one_word(var_content) || (i && str_starts_with_space(var_content)) || (word[i + ft_strlen(var_name) + 1] && str_ends_with_space(var_content)))
			{
				display_ambiguous_redirect(var_name);
				cmd_node->delete_this_node = 1;
			}
			i += ft_strlen(var_name);
			free(var_name);
			free(var_content);
		}
		if (cmd_node->delete_this_node == 1)
			return (0);
		i++;
	}
	return (1);

}
