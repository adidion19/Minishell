/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:04:55 by artmende          #+#    #+#             */
/*   Updated: 2021/12/01 18:21:06 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int	have_redirection_symbol_not_alone(char	*str)
{
	int				have_redirection;
	int				have_something_else;
	t_quote_state	quote;

	have_redirection = 0;
	have_something_else = 0;
	ft_memset(&quote, 0, sizeof(quote));
	while (*str)
	{
		update_quote_state(str, &quote);
		if ((*str == '<' || *str == '>') && quote.global_quote == 0)
			have_redirection = 1;
		if (*str != '<' && *str != '>' && *str != ' ')
			have_something_else = 1;
		str++;
	}
	if (have_redirection && have_something_else)
		return (1);
	else
		return (0);
}

int	have_unquoted_space(char *str)
{
	t_quote_state	quote;

	ft_memset(&quote, 0, sizeof(quote));
	while (str && *str)
	{
		update_quote_state(str, &quote);
		if (ft_isspace(*str) && quote.global_quote == 0)
			return (1);
		str++;
	}
	return (0);
}

/*
	remove_quotes_from_word :

	needs to receive i as 0, this trick is to save 2 lines, thank you the Norm !

	The original word is not freed, need to do it in the calling function.
*/

char	*remove_quotes_from_word(char *word, int i)
{
	char	*scnd_quote;
	char	*cursor;
	void	**ptrarray;

	ptrarray = 0;
	cursor = word;
	while (cursor && cursor[i])
	{
		if (cursor[i] == '\'' || cursor[i] == '"')
		{
			scnd_quote = ft_strchr(&cursor[i + 1], cursor[i]);
			if (scnd_quote)
			{
				ptrarray = add_ptr_to_ptrarray(ptrarray, &cursor[i]);
				ptrarray = add_ptr_to_ptrarray(ptrarray, scnd_quote);
				cursor = scnd_quote;
				i = 0;
			}
		}
		i++;
	}
	word = remove_chars_from_str(word, ptrarray);
	free(ptrarray);
	return (word);
}

void	clean_cmd_node(t_lst_cmd *node)
{
	free_array_of_string(node->arg);
	node->arg = 0;
	free(node->command);
	node->command = 0;
	free(node->inf);
	node->inf = 0;
	free(node->outf);
	node->outf = 0;
}

/*
	A word is defined as characters separated by unquoted white spaces.
	It can also be separated by begining and end of the string.
	It can be 1 char long.
	get_end_of_word returns the address of the last char of the word.
*/

char	*get_end_of_word(char *str)
{
	t_quote_state	quote;

	if (!str)
		return (NULL);
	if (*str == 0)
		return (NULL);
	ft_memset(&quote, 0, sizeof(quote));
	while (*str)
	{
		update_quote_state(str, &quote);
		if (quote.global_quote == 0 && ft_isspace(*str) == 1)
			break ;
		str++;
	}
	return (str - 1);
}
