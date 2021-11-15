/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:07:27 by artmende          #+#    #+#             */
/*   Updated: 2021/11/15 16:58:25 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

char	*copy_next_word(char *from, char **adrs_of_original_ptr)
{
	if (!from || *from != ' ')
		//SYNTAX ERROR ! We have a < that is followed by garbage value
	while (*from == ' ')
		from++;
	// we can have something like << or <> so still need to understand how to handle that

	// the idea is to allocate and copy what follows the '<' and substitute it with var and getenv if necessary
	// then update the adrs_of_original_ptr so that the main loop can continue
}

void	extract_input(t_lst_cmd *node, char *from, char *to)
{
	// for now it will remain 0
/* 
	t_quote_state	quote;

//	node->input_fd = DEFAULT_VALUE; // input_str can remain NULL
	ft_memset(&quote, 0, sizeof(quote));
	while (from && to && from < to) // pointer increases when we browse the str
	{
		update_quote_state(*from, &quote);
		if (*from == '<' && quote.global_quote == 0)
			node->inf = copy_next_word(from + 1, &from);
		from++;
	}
 */

}

void	extract_output(t_lst_cmd *node, char *from, char *to)
{

}
char	*get_end_of_word(char *from, char *to)
{
	t_quote_state	quote;

	ft_memset(&quote, 0, sizeof(quote));
	// find the end of the word (can be a space, or can be "to")
	while (from && to && from < to)
	{
		update_quote_state(*from, &quote);
		if (quote.global_quote == 0 && ft_isspace(*from) == 1)
			break ;
		from++;
	}
	return (from);
}

void	extract_string_array(t_lst_cmd *node, char *from, char *to)
{
	// syntax is : CMD + ARG1 + ARG2 + ... + ARGN
	// at this point there are no redirection left in the line we read
	// 1. browse the string and add a new node in a word linked list for each new word
	// 2. Callocate the array for enough words
	// 3. copy all words inside of the array
	// 4. free the word linked list, but not the words themselves

	char			*end_of_word;
	t_words_list	*words_list;

	words_list = 0;
	while (from && to && from < to)
	{
		// first pass all space that would come before the word
		while (from < to && ft_isspace(*from))
			from++;
		end_of_word = get_end_of_word(from, to);
		words_list = add_word_to_list(words_list, from, end_of_word);
		from = end_of_word;
	}
	// at this point the linked list exist and contains all the words.

	// we calloc for lstsize + 1 strings, and we copy all string in the array in order
	node->arg = ft_calloc(sizeof(char *) * (1 + ft_lstsize_words(words_list)));
	if (!node->arg)
		return ((void)(free_word_list(words_list, 1))); // if we can't allocate the array, we free the whole list including the words
	copy_args_from_word_list(node->arg, words_list);

	// free the linked list
	free_word_list(words_list, 0);
}

t_lst_cmd	*add_pipe_section(t_lst_cmd *list, char *from, char *to)
{
	t_lst_cmd	*ret;
	t_lst_cmd	*temp;

	ret = ft_calloc(sizeof(t_lst_cmd));
	if (!ret)
		return (list); // in case allocation fail, we still have to return previous nodes to be able to free them
	extract_input(ret, from, to);
	extract_output(ret, from, to);
	extract_string_array(ret, from, to);
	ret->next = 0; // no need, it's already 0 by default
	// what if one extract fails ?
	if (!list)
		return (ret);
	temp = list;
	while (temp && temp->next)
		temp = temp->next;
	// temp points now to the last element of the list
	temp->next = ret;
	return (list);
}

t_lst_cmd	*parser(char *line)
{
	t_lst_cmd		*ret;
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



//	printf("%s\n", getenv("COUCOUU"));
	// getenv returns a null pointer when it didnt find the matching variable
/* 	int	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	} */
	if (argc > 1)
	{
		printf("\n%s\n\n", argv[1]);
//		parser(argv[1]);
	}
	return (0);
}
