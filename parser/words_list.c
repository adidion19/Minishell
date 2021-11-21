/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:32:30 by artmende          #+#    #+#             */
/*   Updated: 2021/11/21 18:27:25 by artmende         ###   ########.fr       */
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
**	free_word_list : if flag is non null, the words themselves are freed too.
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
