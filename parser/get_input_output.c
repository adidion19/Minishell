/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:08:05 by artmende          #+#    #+#             */
/*   Updated: 2021/12/08 16:55:17 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

/*
	get_input_output : 

	Browse the words list looking for unquoted redirection symbols.
	For each of them, verify that the associated word is correct.
	If the name is correct, open (create) the associated file and keep the name
	in the cmd_node.
	We don't keep the fd, because unused files need to be closed.

	If the file name is incorrect, we display the ambiguous redirect message and
	we stop parsing that pipe section.
	cmd_node->delete_this_node is set to 1 to indicate that we have to stop
	parsing, that's done by the function that displays the error message.

	The associated nodes from words_list are deleted after they have been
	handled.
*/

t_words_list	*get_input_output(t_lst_cmd *cmd_node, t_words_list *words_lst,
	char **env)
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
			temp = add_output_no_append(cmd_node, temp, &words_lst, env);
		else if (!ft_strcmp(temp->word, ">>"))
			temp = add_output_append(cmd_node, temp, &words_lst, env);
		else if (!ft_strcmp(temp->word, "<"))
			temp = add_input(cmd_node, temp, &words_lst, env);
		else if (!ft_strcmp(temp->word, "<<"))
			temp = add_heredoc(cmd_node, temp, &words_lst);
		else
			temp = temp->next;
	}
	return (words_lst);
}

char	*resolve_redir_name(t_lst_cmd *cmd_node, char *word, char **env)
{
	char	*ret;
	char	*temp;

	if (!verify_redir_var(cmd_node, word, env))
		return (NULL);
	temp = expand_variables_in_single_word(word, env);
	ret = remove_quotes_from_word(temp, 0);
	free(temp);
	return (ret);
}

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
		write(2, "exotic_shell: ", 14);
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
		write(2, "exotic_shell: ", 14);
		write(2, cmd_node->inf, ft_strlen(cmd_node->inf));
		write (2, ": ", 2);
		write(2, strerror(error), ft_strlen(strerror(error)));
		write(2, "\n", 1);
		cmd_node->delete_this_node = 1;
	}
	else
		close(fd);
}
