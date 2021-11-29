/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:08:05 by artmende          #+#    #+#             */
/*   Updated: 2021/11/29 16:13:18 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"


void	open_outfile(t_lst_cmd *cmd_node)
{
	int	fd;
	int	error;

	errno = 0;
	if (cmd_node->append)
		fd = open(cmd_node->outf, O_WRONLY | O_CREAT, 00644);
	else
		fd = open(cmd_node->outf, O_WRONLY | O_TRUNC | O_CREAT, 00644);
	error = errno;
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		write(2, cmd_node->outf, ft_strlen(cmd_node->outf));
		write (2, ": ", 2);
		write(2, strerror(error), ft_strlen(strerror(error)));
		write(2, "\n", 1);
		cmd_node->delete_this_node = 1;
	}
	else
		close(fd);
}

void	open_infile(t_lst_cmd *cmd_node)
{
	int	fd;
	int	error;

	errno = 0;
	fd = open(cmd_node->inf, O_RDONLY);
	error = errno;
	if (fd == -1)
	{
		write(2, "minishell: ", 11);
		write(2, cmd_node->inf, ft_strlen(cmd_node->inf));
		write (2, ": ", 2);
		write(2, strerror(error), ft_strlen(strerror(error)));
		write(2, "\n", 1);
		cmd_node->delete_this_node = 1;
	}
	else
		close(fd);
}




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


char	*resolve_redir_name(t_lst_cmd *cmd_node, char *word)
{
	// abc$(var)'more word'"   $(   more var   )"def
	// becomes : "abcvarmore word      more var   def"
	
	// return value is the final name of file
	// in case of error, write in the cmd_node that this node is not to be executed
	// word is the raw name, with still quotes and dollar symbol
// is there an unquoted dollar ?? real unquoted
// does that variable contain more than one word inside of it ? --> bash: gb$TEST: ambiguous redirect
// if the variable contains max 1 word (nothing is less than one word too), expand it
// then concatenate with the rest if there is something else
// after removing quotes, thats the final file name

//	possible errors :
//	unquoted var that contains more than one word
//	unquoted var that starts with spaces and var is preceded by something
//	unquoted var that finishes with spaces and is followed by something

//	if dollar var is OUTSIDE quotes, trim the spaces
//	if dollar var is INSIDE double quotes, keep the spaces

	char	*ret;
	char	*temp;



	if (!verify_redir_var(cmd_node, word)) // put to_delete to 1
		return (NULL);

	temp = expand_variables_in_single_word(word);
	ret = remove_quotes_from_word(temp, 0);
	free(temp);

	return (ret);

}




t_words_list	*add_output_no_append(t_lst_cmd *cmd_node, t_words_list *node,
	t_words_list **words_lst)
{
	// need to receive the node, to access its next, and free both himself and the next
	// need to receive the list, to free nodes inside of it, and modify it --> double pointer here !
	// need to receive the cmd_node 

	free(cmd_node->outf); // will be 0 at first, but can be previous redir
	cmd_node->outf = resolve_redir_name(cmd_node, node->next->word);
	cmd_node->append = 0;
	if (cmd_node->outf)
		open_outfile(cmd_node); // possible error : no right to open
	*words_lst = delete_node_words_list(*words_lst, node->next);
	*words_lst = delete_node_words_list(*words_lst, node);
	return (*words_lst);
}

t_words_list	*add_output_append(t_lst_cmd *cmd_node, t_words_list *node,
	t_words_list **words_lst)
{
	free(cmd_node->outf); // will be 0 at first, but can be previous redir
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

t_words_list	*get_input_output(t_lst_cmd *cmd_node, t_words_list *words_lst)
{
	t_words_list	*temp;

	temp = words_lst;
	while (temp)
	{
		if (cmd_node->delete_this_node == 1)
		{
			clean_cmd_node(cmd_node);
			break ;
		}
		if (!ft_strcmp(temp->word, ">"))
			temp = add_output_no_append(cmd_node, temp, &words_lst); // words_lst is updated inside the function
		else if (!ft_strcmp(temp->word, ">>"))
			temp = add_output_append(cmd_node, temp, &words_lst);
		else if (!ft_strcmp(temp->word, "<"))
			temp = add_input(cmd_node, temp, &words_lst); // reassign words_lst inside of that function
		else if (!ft_strcmp(temp->word, "<<"))
			temp = add_heredoc(cmd_node, temp, &words_lst);
		else
			temp = temp->next;
	}
	return (words_lst);
}




// at the end, check that the length of the file name is not 0
//bash: : No such file or directory

// catching error when opening the file ?
