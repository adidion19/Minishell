/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:32:30 by artmende          #+#    #+#             */
/*   Updated: 2021/11/29 15:40:44 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int	have_redirection_symbol_not_alone(char	*str)
{
/* 	size_t	len;

	len = ft_strlen(str);
	if (len < 2 || (!ft_strnstr(str, "<", len) && !ft_strnstr(str, ">", len)))
		return (0);
	if (ft_strnstr(str, "<", len))
	{
		if (!ft_strnstr(str, "<<", len) && len > 1)
			return (1);
		if (ft_strnstr(str, "<<", len) && len > 2)
			return (1);
	}
	if (ft_strnstr(str, ">", len))
	{
		if (!ft_strnstr(str, ">>", len) && len > 1)
			return (1);
		if (ft_strnstr(str, ">>", len) && len > 2)
			return (1);
	}
	return (0); */

	int		have_redirection;
	int		have_something_else;
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

t_words_list	*create_word_node(char	*word)
{
	t_words_list	*ret;

	ret = ft_calloc(sizeof(t_words_list));
	if (!ret)
		exit(EXIT_FAILURE);
	ret->word = word;
	return (ret);
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




t_words_list	*split_words_with_redirection_symbols(t_words_list *list)
{
	// separating something like that : 
	//	<file1<file2<<EOF>file3>file4>>file5>file6
	//	cmd<infile>outfile

	t_words_list	*temp;

	temp = list;
	while (temp)
	{
		if (have_redirection_symbol_not_alone(temp->word))
		{
/* 			printf("\n");
			display_words_list(list);
			printf("\n");
			usleep(500); */
			
			insert_nodes_split_word(temp, temp->word, "<>", 1);
			temp = delete_node_words_list(list, temp);
			list = temp;
			continue ;
		}
		temp = temp->next;
	}
	return (list);
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
		if (str <= end_of_word)
		{
			words_list = add_word_to_list(words_list,
					duplicate_part_of_str(str, end_of_word));
		}
		str = end_of_word + 1; // end of word is the last char of the word, we want to get past that
	}

	words_list = split_words_with_redirection_symbols(words_list);
	// at this point the linked list exist and contains all the words.
//	expand_variables_in_words_list(words_list);
	// at this point all $var are expanded. quotes are still there
//	remove_quotes_in_words_list(words_list);

//	we won't do anything more here. We need to get the redirections first
	return (words_list);
}

t_words_list	*add_word_to_list(t_words_list *lst, char *word)
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
