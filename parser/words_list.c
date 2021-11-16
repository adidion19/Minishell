/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:32:30 by artmende          #+#    #+#             */
/*   Updated: 2021/11/16 14:24:04 by artmende         ###   ########.fr       */
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

t_words_list	*add_word_to_list(t_words_list *lst, char *from, char *to)
{
	t_words_list	*ret;
	t_words_list	*temp;
	int				i;

	ret = ft_calloc(sizeof(t_words_list));
	if (!ret)
		return (lst);
	ret->word = ft_calloc(sizeof(char) * (1 + (to - from)));
	if (!ret->word)
	{
		free(ret);
		return(lst);
	}
	i = 0;
	while (&from[i] <= to)
		ret->word[i] = from[i++];
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

