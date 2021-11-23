/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:08:05 by artmende          #+#    #+#             */
/*   Updated: 2021/11/23 16:31:20 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

/*
	get_input_output : 

	Browse the words list looking for unquoted redirection symbol.
	For each of them, verify that the associated word is correct
	If it is correct, open the associated file and keep the name in the cmd_node
	we don't keep the fd, because unused files need to be closed
	deleted the node from words_list after it has been handled 

*/

t_words_list	*get_input_output(t_lst_cmd *cmd_node, t_words_list *words_lst)
{
	t_words_list	*temp;

	temp = words_lst;
	while (temp)
	{
		if (ft_strlen(temp->word) == 1 && temp->word[0] == '>')
		{
			temp = add_output_no_append();
			words_lst = temp;
		}
		else if (ft_strlen(temp->word) == 2 && ft_strnstr(temp->word, ">>", 2))
		{
			temp = add_output_append();
			words_lst = temp;
		}
		else if (ft_strlen(temp->word) == 1 && temp->word[0] == '<')
		{
			temp = add_input(); // reassign words_lst inside of that function
			words_lst = temp;
		}
		else if (ft_strlen(temp->word) == 2 && ft_strnstr(temp->word, "<<", 2))
		{
			temp = add_heredoc();
			words_lst = temp;
		}
		// need to verify that we don't have something like <<< or <>< 
		// have unquoted < or > + (have mixed or have length more than 2)
		// actually if still have unquoted < or > here it means error
		// otherwise it would have been catched above
		else
			temp = temp->next;
	}
	return (words_lst);
}