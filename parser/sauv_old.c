/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sauv_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:44:15 by artmende          #+#    #+#             */
/*   Updated: 2021/11/28 18:45:54 by artmende         ###   ########.fr       */
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

void	display_words_list(t_words_list	*list)
{
	printf("Displaying words_list...\n");
	while (list)
	{
		printf("Word -> %s\n", list->word);
		list = list->next;
	}
	printf("Done !\n");
}

int	display_syntax_error(char c)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, &c, 1);
	write(2, "'\n", 2);
	return (0);
}

int	display_ambiguous_redirect(t_lst_cmd *cmd_node, char *var_name)
{
	cmd_node->delete_this_node = 1;
	write(2, "minishell: $", 12);
	write(2, var_name, ft_strlen(var_name));
	write(2, ": ambiguous redirect\n", 21);
	return (0);
}

/*
	remove_quotes_from_word :

	needs to receive i as 0, use it to save 2 lines.

	original word is not free, need to do it in the calling function.

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
coucou"je suis 'la et toi' et"kehbfhj'jhebhjbe" ejhvejghj  "shjebgehj'jshebgehj

coucouje suis 'la et toi' etkehbfhjjhebhjbe" ejhvejghj  "shjebgehjjshebgehj

 */