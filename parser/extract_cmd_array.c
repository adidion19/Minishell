/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:11:18 by artmende          #+#    #+#             */
/*   Updated: 2021/11/29 14:26:20 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

void	extract_cmd_array(t_lst_cmd *node, char *str) // to delete
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
	while (*str)
	{
		// first pass all space that would come before the word
		while (ft_isspace(*str))
			str++;
		end_of_word = get_end_of_word(str);
//		words_list = add_word_to_list(words_list, str, end_of_word);
		str = end_of_word;
	}
	// at this point the linked list exist and contains all the words.

	// we calloc for lstsize + 1 strings, and we copy all string in the array in order
	node->arg = ft_calloc(sizeof(char *) * (1 + ft_lstsize_words(words_list)));
	if (!node->arg)
		return ((void)(free_words_list(words_list, 1))); // if we can't allocate the array, we free the whole list including the words
	copy_args_from_word_list(node->arg, words_list);

	// free the linked list
	free_words_list(words_list, 0);
}


