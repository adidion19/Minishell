/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_list_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:15:46 by artmende          #+#    #+#             */
/*   Updated: 2021/12/01 17:21:01 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

t_words_list	*split_words_with_spaces_in_words_list(t_words_list *list)
{
	t_words_list	*temp;

	temp = list;
	while (temp)
	{
		if (have_unquoted_space(temp->word))
		{
			insert_nodes_split_word(temp, temp->word, "\t\n\r\v\f ", 0);
			temp = delete_node_words_list(list, temp);
			list = temp;
			continue ;
		}
		temp = temp->next;
	}
	return (list);
}

/*
	insert_nodes_split_word :

	Duplicate and split the word of the first node of the list in max 3 nodes.

	One node for whatever is before the first group of char defined in sep.
	One node for the group of separators (can be skipped if include_sep is 0).
	One node for whatever is left after.

	The original node stays where it was, with the splitted nodes added just
	after it, and the rest of the list attached after the splitted nodes.

	The pointer "word" originally points to the beginning of the original
	string.
	After each insertion, the pointer "word" is updated to point to the char in
	the original string that follows what was just inserted.

	The pointer temp points originally to the first node, then it is updated to
	points to the last node inserted.
*/

void	insert_nodes_split_word(t_words_list *list, char *word, char *sep,
	int include_sep)
{
	t_quote_state	quote;
	t_words_list	*sav_next;
	t_words_list	*temp;
	char			*cursor;

	ft_memset(&quote, 0, sizeof(quote));
	sav_next = list->next;
	temp = list;
	temp->next = 0;
	cursor = word;
	while (*cursor && update_quote_state(cursor, &quote)
		&& (quote.global_quote == 1 || !ft_strchr(sep, *cursor)))
		cursor++;
	temp = insert_splitted_word(&word, cursor, temp);
	while (*cursor && ft_strchr(sep, *cursor))
		cursor++;
	if (include_sep)
		temp = insert_splitted_word(&word, cursor, temp);
	else
		word = cursor;
	while (*cursor)
		cursor++;
	temp = insert_splitted_word(&word, cursor, temp);
	temp->next = sav_next;
}

/*
	insert_splitted_word :

	from is updated in the parent function.
*/

t_words_list	*insert_splitted_word(char **from, char *to, t_words_list *node)
{
	if (to != *from)
		node->next = create_word_node(duplicate_part_of_str(*from, to - 1));
	*from = to;
	if (node->next)
		return (node->next);
	return (node);
}

t_words_list	*create_word_node(char	*word)
{
	t_words_list	*ret;

	ret = ft_calloc(sizeof(t_words_list));
	if (!ret)
		exit(EXIT_FAILURE);
	ret->word = word;
	return (ret);
}

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
