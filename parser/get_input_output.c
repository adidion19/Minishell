/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:08:05 by artmende          #+#    #+#             */
/*   Updated: 2021/11/22 13:31:12 by artmende         ###   ########.fr       */
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
		if (temp->word)
		{

		}
		temp = temp->next;
	}
	return (0);
}