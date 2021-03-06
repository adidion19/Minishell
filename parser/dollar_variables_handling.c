/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_variables_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:36:46 by artmende          #+#    #+#             */
/*   Updated: 2021/12/13 10:48:12 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int	have_var_to_expand(char *word)
{
	t_quote_state	quote;

	ft_memset(&quote, 0, sizeof(quote));
	while (word && *word)
	{
		update_quote_state(word, &quote);
		if (*word == '$' && quote.simple_quote == 0 && *(word + 1)
			&& is_valid_var_char(*(word + 1)))
		{
			return (1);
		}
		word++;
	}
	return (0);
}

/*
	expand_variables_in_words_list

	Browse the list and replace each word by a copy with variable expanded.
	If length of word in 0 after expanding, delete this word from the list.
*/

t_words_list	*expand_variables_in_words_list(t_words_list *list, char **env)
{
	t_words_list	*temp_list;
	char			*temp_word;

	temp_list = list;
	while (temp_list)
	{
		temp_word = expand_variables_in_single_word(temp_list->word, env);
		if (have_var_to_expand(temp_list->word) && ft_strlen(temp_word) == 0)
		{
			free(temp_word);
			list = delete_node_words_list(list, temp_list);
			temp_list = list;
			continue ;
		}
		free(temp_list->word);
		temp_list->word = temp_word;
		temp_list = temp_list->next;
	}
	return (list);
}

/*
	expand_variables_in_single_word

	Returns an allocated string with variables expanded. Original string in not
	freed.
*/

char	*expand_variables_in_single_word(char *word, char **env)
{
	int				i;
	char			*ret;
	char			*var_name;
	char			*var_content;
	t_quote_state	quote;

	ft_memset(&quote, 0, sizeof(quote));
	ret = 0;
	while (word && *word)
	{
		i = 0;
		while (word[i] && !(word[i] == '$' && !quote.simple_quote && word[i + 1]
				&& is_valid_var_char(word[i + 1])))
			(void)(update_quote_state(&word[i], &quote) && ++i);
		ret = malagain(ret, word, i);
		if (word[i] == 0)
			break ;
		var_name = get_var_name(&word[i]);
		var_content = get_var_content(var_name, quote, env);
		ret = malagain(ret, var_content, ft_strlen(var_content));
		word = &word[i] + ft_strlen(var_name) + 1;
		free(var_name);
		free(var_content);
	}
	return (ret);
}

char	*get_var_name(char *str)
{
	char	*cursor;

	str++;
	cursor = str;
	if (str && str[0] == '?')
		return (ft_strdup("?"));
	if (ft_isdigit(*cursor))
		return (duplicate_part_of_str(cursor, cursor));
	while (*cursor)
	{
		if (*cursor != '_' && !ft_isalnum(*cursor))
			break ;
		cursor++;
	}
	if (cursor == str)
		return (ft_strdup(""));
	return (duplicate_part_of_str(str, cursor - 1));
}

/*
	get_var_content :

	If the var is outside quotes, we have to trim the whitespaces around its
	content.
*/

char	*get_var_content(char *var_name, t_quote_state quote, char **env)
{
	char	*raw_value;

	if (var_name && var_name[0] == '?')
		return (ft_itoa(g_global.status));
	raw_value = env_find_no_malloc_no_equal(var_name, env);
	if (ft_strlen(raw_value) == 0)
		return (ft_strdup(""));
	if (quote.double_quote)
		return (ft_strdup(raw_value));
	else
		return (ft_strtrim(raw_value, "\t\n\r\v\f "));
}
