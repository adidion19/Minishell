/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:32:30 by artmende          #+#    #+#             */
/*   Updated: 2021/11/17 18:13:32 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int	ft_lstsize_words(t_words_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_words_list	*create_words_list(char *str)
{
	char			*end_of_word;
	t_words_list	*words_list;

	words_list = 0;
	while (*str)
	{
		// first pass all space that would come before the word
		while (ft_isspace(*str))
			str++;
		end_of_word = get_end_of_word(str);
		words_list = add_word_to_list(words_list, str, end_of_word);
		str = end_of_word;
	}
	// at this point the linked list exist and contains all the words.
	return (words_list);
}

/* 
	instead of copying from 2 pointers, we should receive the duplicated str from
	end_of_word (get_word ?) and simply add it to the node.

	get_word would either take it from the string itself, or resolve a substitution
	or something with quote, but that's fucked up because that can be more than
	one word

	maybe take a word and call a new function that will interpret quotes etc and 
	create as many nodes as needed

	associate a variable in node like "int	is_a_marker" that would have 0 as default

 */

t_words_list	*add_word_to_list(t_words_list *lst, char *from, char *to)
{
	t_words_list	*ret;
	t_words_list	*temp;
	int				i;

	ret = ft_calloc(sizeof(t_words_list));
	if (!ret)
		exit(EXIT_FAILURE);
	ret->word = ft_calloc(sizeof(char) * (1 + (to - from)));
	if (!ret->word)
		exit(EXIT_FAILURE);
	i = 0;
	while (&from[i] <= to)
	{
		ret->word[i] = from[i];
		i++;
	}
	if (!lst)
		return (ret);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	temp->next = ret;
	return (lst);
}

void	copy_args_from_word_list(char **array, t_words_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		// substitute word
		array[i] = list->word;
		i++;
		list = list->next;
	}
}

/*
**	free_word_list : if flag is non null, we free the words themselves too
*/

void	free_word_list(t_words_list *list, int flag)
{
	t_words_list	*temp;
	
	while (list)
	{
		temp = list->next;
		if (flag)
			free(list->word);
		free(list);
		list = temp;
	}
}

