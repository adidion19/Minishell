/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sauv_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:44:15 by artmende          #+#    #+#             */
/*   Updated: 2021/11/21 18:26:26 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

void	copy_args_from_word_list(char **array, t_words_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		array[i] = list->word;
		i++;
		list = list->next;
	}
}


int		is_there_unquoted_dollar(char *str)
{
	t_quote_state	quote;

	ft_memset(&quote, 0, sizeof(quote));
	while (str && *str)
	{
		update_quote_state(str, &quote);
		if (*str == '$' && quote.simple_quote == 0 && *(str + 1)
			&& !ft_isspace(*str + 1))
		{
			return (1);
		}
		str++;
	}
	return (0);
}

char	*get_dollar_name(char *str)
{
	char	*cursor;
	char	*ret;
	int		i;

	str++;
	cursor = str;
	while (*cursor)
	{
		if (*cursor == '\'' || *cursor == '"' || ft_isspace(*cursor))
			break ;
		cursor++;
	}
	ret = ft_calloc(sizeof(char) * (cursor - str));
	if (!ret)
		exit(EXIT_FAILURE);
	i = 0;
	while (str < cursor)
	{
		ret[i] = *str;
		i++;
		str++;
	}
	return (ret);
}



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
	t_quote_state	quote;
	
	ft_memset(&quote, 0, sizeof(quote));
	ret = 0;
	i = 0;
	while (word && word[i])
	{
		i = 0;
		while (word[i] && !(word[i] == '$' && quote.simple_quote == 0 && word[i + 1] && !ft_isspace(word[i + 1]))) // browse until we find a $ to expand
		{
			update_quote_state(&word[i], &quote);
			i++;
		} // i is the number of char to copy
		ret = malagain(ret, word, i); // we add i char from word to ret
		var_name = get_dollar_name(&word[i]);
		ret = malagain(ret, getenv(var_name), ft_strlen(getenv(var_name))); // if the variable doesnt exist, getenv is null pointer
		free(var_name);
		word = &word[i] + ft_strlen(var_name) + 1; // we go directly to after the variable name. we start from the $ (&word[i]) and we add the length of var + 1 (for the $)
	}
	return (ret);
}

void	expand_variables_in_words_list(t_words_list *list)
{
	t_words_list	*temp_list;
	char			*temp_word;

	printf("I was called\n");

	temp_list = list;
	while (temp_list)
	{
		if (is_there_unquoted_dollar(temp_list->word))
		{
			// browse the word until the $
			// follow the $ until either a space or a quote sign
			// copy all that was before the $ and copy the value and copy all that is after it
			// free previous word and replace it with new one created
			
			// if the word before it was a <, it's ok because we will see after that the word contains spaces or not
			temp_word = expand_variables_in_single_word(temp_list->word);
			free(temp_list->word);
			temp_list->word = temp_word;
		}
		temp_list = temp_list->next;
	}
}
