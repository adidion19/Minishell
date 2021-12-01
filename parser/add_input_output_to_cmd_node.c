/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_input_output_to_cmd_node.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:26:08 by artmende          #+#    #+#             */
/*   Updated: 2021/12/01 17:49:10 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

/*
	A pipe section can have only one input and one output.
	Adding a new (in/out)file will then overwrite the one that was there before.

	The (int/out)file is opened (created) and then closed.

	The nodes in wordslist that contain the redirections are deleted after they
	have been handled, so that only the command and its arguments remain in the
	words list after get_input_output returns.
*/

t_words_list	*add_output_no_append(t_lst_cmd *cmd_node, t_words_list *node,
	t_words_list **words_lst)
{
	free(cmd_node->outf);
	cmd_node->outf = resolve_redir_name(cmd_node, node->next->word);
	cmd_node->append = 0;
	if (cmd_node->outf)
		open_outfile(cmd_node);
	*words_lst = delete_node_words_list(*words_lst, node->next);
	*words_lst = delete_node_words_list(*words_lst, node);
	return (*words_lst);
}

t_words_list	*add_output_append(t_lst_cmd *cmd_node, t_words_list *node,
	t_words_list **words_lst)
{
	free(cmd_node->outf);
	cmd_node->outf = resolve_redir_name(cmd_node, node->next->word);
	cmd_node->append = 1;
	if (cmd_node->outf)
		open_outfile(cmd_node);
	*words_lst = delete_node_words_list(*words_lst, node->next);
	*words_lst = delete_node_words_list(*words_lst, node);
	return (*words_lst);
}

t_words_list	*add_input(t_lst_cmd *cmd_node, t_words_list *node,
	t_words_list **words_lst)
{
	free(cmd_node->inf);
	cmd_node->inf = resolve_redir_name(cmd_node, node->next->word);
	if (cmd_node->inf)
		open_infile(cmd_node);
	cmd_node->heredoc = 0;
	*words_lst = delete_node_words_list(*words_lst, node->next);
	*words_lst = delete_node_words_list(*words_lst, node);
	return (*words_lst);
}

t_words_list	*add_heredoc(t_lst_cmd *cmd_node, t_words_list *node,
	t_words_list **words_lst)
{
	char	*temp;

	free(cmd_node->inf);
	temp = ft_strdup(node->next->word);
	cmd_node->inf = remove_quotes_from_word(temp, 0);
	free(temp);
	cmd_node->heredoc = 1;
	*words_lst = delete_node_words_list(*words_lst, node->next);
	*words_lst = delete_node_words_list(*words_lst, node);
	return (*words_lst);
}
