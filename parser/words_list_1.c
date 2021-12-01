/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_list_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:32:30 by artmende          #+#    #+#             */
/*   Updated: 2021/12/01 18:21:29 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

t_words_list	*create_words_list(char *str)
{
	char			*end_of_word;
	t_words_list	*words_list;

	words_list = 0;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		end_of_word = get_end_of_word(str);
		if (str <= end_of_word)
		{
			words_list = addback_word_to_list(words_list,
					duplicate_part_of_str(str, end_of_word));
		}
		if (end_of_word)
			str = end_of_word + 1;
	}
	words_list = split_words_with_redirection_symbols(words_list);
	return (words_list);
}

t_words_list	*addback_word_to_list(t_words_list *lst, char *word)
{
	t_words_list	*ret;
	t_words_list	*temp;

	if (!word)
		exit(EXIT_FAILURE);
	ret = ft_calloc(sizeof(t_words_list));
	if (!ret)
		exit(EXIT_FAILURE);
	ret->word = word;
	if (!lst)
		return (ret);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	temp->next = ret;
	return (lst);
}

/*
	split_words_with_redirection_symbols :

	separating something like that : 
	<file1<file2<<EOF>file3>file4>>file5>file6
	cmd<infile>outfile

	delete_node_words_list returns the head of the list.
*/

t_words_list	*split_words_with_redirection_symbols(t_words_list *list)
{
	t_words_list	*temp;

	temp = list;
	while (temp)
	{
		if (have_redirection_symbol_not_alone(temp->word))
		{
			insert_nodes_split_word(temp, temp->word, "<>", 1);
			temp = delete_node_words_list(list, temp);
			list = temp;
			continue ;
		}
		temp = temp->next;
	}
	return (list);
}

t_words_list	*delete_node_words_list(t_words_list *list, t_words_list *node)
{
	t_words_list	*temp;

	if (!list || !node)
		return (NULL);
	if (node == list)
	{
		temp = list->next;
		free(list->word);
		free(list);
		return (temp);
	}
	else if (node == list->next)
	{
		temp = node->next;
		free(node->word);
		free(node);
		list->next = temp;
		return (list);
	}
	else
	{
		delete_node_words_list(list->next, node);
		return (list);
	}
}

/*
**	free_words_list : if flag is non null, the words themselves are freed too.
*/

int	free_words_list(t_words_list *list, int flag)
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
	return (1);
}
