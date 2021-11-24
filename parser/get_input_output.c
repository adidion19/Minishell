/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:08:05 by artmende          #+#    #+#             */
/*   Updated: 2021/11/24 18:11:30 by artmende         ###   ########.fr       */
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

/* 
	possible errors :
	redirection symbol followed by nothing
	redirection symbol followed by another one
	incorrect redirection symbol (like <> or >>>)

	CHECK FOR ERRORS FIRST
	that's done before parsing begins

	dollar variable are separated into words before redirection
	quoted stuff are taken as a single word (single filename)
 */

t_words_list	*add_output_no_append(t_lst_cmd *cmd_node, t_words_list *node, 
	t_words_list **words_lst)
{
	// need to receive the node, to access its next, and free both himself and the next
	// need to receive the list, to free nodes inside of it, and modify it --> double pointer here !
	// need to receive the cmd_node 

	cmd_node->outf = resolve_dollar_quote(node->next->word);
	cmd_node->append = 0;
	create_outfile(cmd_node);
	*words_lst = delete_node_words_list(*words_lst, node->next);
	*words_lst = delete_node_words_list(*words_lst, node);
	return (*words_lst);
}

t_words_list	*add_output_append(t_lst_cmd *cmd_node, t_words_list *node, 
	t_words_list **words_lst)
{
	cmd_node->outf = resolve_dollar_quote(node->next->word);
	cmd_node->append = 1;
	create_outfile(cmd_node);
	*words_lst = delete_node_words_list(*words_lst, node->next);
	*words_lst = delete_node_words_list(*words_lst, node);
	return (*words_lst);
}



t_words_list	*get_input_output(t_lst_cmd *cmd_node, t_words_list *words_lst)
{
	t_words_list	*temp;

	temp = words_lst;
	while (temp)
	{
		if (!ft_strcmp(temp->word, ">"))
			temp = add_output_no_append(cmd_node, temp, &words_lst); // words_lst is updated inside the function
		else if (!ft_strcmp(temp->word, ">>"))
			temp = add_output_append(cmd_node, temp, &words_lst);
		else if (!ft_strcmp(temp->word, "<"))
		{
//			temp = add_input(); // reassign words_lst inside of that function
			words_lst = temp;
		}
		else if (!ft_strcmp(temp->word, "<<"))
		{
//			temp = add_heredoc();
			words_lst = temp;
		}
		else
			temp = temp->next;
	}
	return (words_lst);
}