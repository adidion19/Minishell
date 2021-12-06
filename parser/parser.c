/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:07:27 by artmende          #+#    #+#             */
/*   Updated: 2021/12/06 17:19:54 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

/*
	Parser : General explanation

	The parser separate a line with unquoted pipe symbol as separator.
	For each "pipe section", a node in a command list will be created.
	For each "pipe section", the section is first separated in words.
	Those words are stored in a words list.

	When we have the first list of words (with variables and quotes still
	untouched), we look for infile and outfile.
	Nodes corresponding to redirection will be deleted from the word list after
	they are handled.
	We have to resolve variables and remove quotes for only the redirections
	word at this stage.

	After the redirection stage is finished, we are left with a word list that
	contains only the command and the args.
	That's when we resolve all other variables and quotes.

	after quotes and variables have been resolved, we copy all words from the
	list into the final args array for this pipe section.
*/

t_lst_cmd	*parser(char *line)
{
	t_lst_cmd		*ret;
	t_quote_state	quote;
	char			*cursor;

	if (!line || !verify_pipe_conditions(line) || !verify_redirections(line))
		return (NULL);
	ft_memset(&quote, 0, sizeof(quote));
	ret = 0;
	cursor = line;
	while (*line)
	{
		while (*cursor)
		{
			update_quote_state(cursor, &quote);
			if (*cursor == '|' && quote.global_quote == 0)
				break ;
			cursor++;
		}
		ret = add_pipe_section(ret, duplicate_part_of_str(line, cursor - 1));
		if (*cursor)
			cursor++;
		line = cursor;
	}
	return (ret);
}

/*
	free_lst_cmd :

	list->command store the same address than list->arg[0].
	No need to free it two times.
*/

t_lst_cmd	*free_lst_cmd(t_lst_cmd *list)
{
	t_lst_cmd	*temp;

	while (list)
	{
		free_array_of_string(list->arg);
		free(list->inf);
		free(list->outf);
		temp = list->next;
		free(list);
		list = temp;
	}
	return (NULL);
}

t_lst_cmd	*reverse_lst_cmd(t_lst_cmd *list)
{
	t_lst_cmd	*before;
	t_lst_cmd	*after;

	before = NULL;
	while (list)
	{
		after = list->next;
		list->next = before;
		before = list;
		list = after;
	}
	return (before);
}
