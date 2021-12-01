/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:07:27 by artmende          #+#    #+#             */
/*   Updated: 2021/12/01 15:32:25 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"


void	handle_cmd_args_in_list(t_lst_cmd *node, t_words_list *words_list)
{
	int				i;
	t_words_list	*temp;

	i = 0;
	if (!words_list || !node)
		return ;
	node->arg = ft_calloc(sizeof(char *) * (1 + ft_lstsize_words(words_list)));
	temp = words_list;
	while (temp)
	{
		node->arg[i] = remove_quotes_from_word(temp->word, 0);
		i++;
		temp = temp->next;
	}
	node->command = node->arg[0];
	free_words_list(words_list, 1);
}










/*
	add_pipe_section :

	First we create the words list.
	It's a linked list of all the words of that pipe section.
	A word is defined as a group of chars separated by unquoted white spaces,
	or by the beginning/end of the string.

	It means that whatever is between quotes is indivisible and stays together.

	Secondly we get the (in/out)files, and we delete the corresponding nodes
	from the words list.

	All that stays in the words list at this point is the command, and its
	arguments.

	We expand the environment variables in the list, and if a variable contains
	more than one word, we separate them and add new nodes in words_list.

	At this point, all that is left is to do is to copy all words from the list
	into an array of string that will be kept in the command list.
	We have to remove quotes from words at that stage.
	
	
	While doing that, we do substitution and we group the quoted things together
	substitution can result in more than one word
	quoted stuff can be merged with letters before or after it to form 1 word

	< > signs can appear in quote or in substitution var

	After the list is made, we 



*/

t_lst_cmd	*add_pipe_section(t_lst_cmd *list, char *str)
{
	t_lst_cmd		*ret;
	t_lst_cmd		*temp;
	t_words_list	*words_list;

	ret = ft_calloc(sizeof(t_lst_cmd));
	if (!ret)
		exit(EXIT_FAILURE);
	words_list = create_words_list(str);
	words_list = get_input_output(ret, words_list);
	if (ret->delete_this_node == 1)
	{
		free_words_list(words_list, 1);
		words_list = 0;
	}
	expand_variables_in_words_list(words_list);
	words_list = split_words_with_spaces_in_words_list(words_list);
	handle_cmd_args_in_list(ret, words_list);
	free(str);
	if (!list)
		return (ret);
	temp = list;
	while (temp && temp->next)
		temp = temp->next;
	temp->next = ret;
	return (list);
}





/* 
	Parser : 
	the parser will separate a line with unquoted pipe symbol as separator.
	for each "pipe section", a node in a cmd list will be created.
	for each "pipe section", the section is first separated in words.
	words are separated by unquoted spaces.

	When we have the first list of words (with variables and quotes still untouched),
	we look for infile and outfile.
	nodes corresponding to redirection will be deleted from the word list after they are handled.
	we have to resolve quotes and variables for only the redirections word at this stage
	that's when we look for redirection error. (redirection word contains space for example or redirection is followed by nothing)

	after the redirection stage is finished, we are left with the word list that contains
	only cmd and args.
	that's when we resolve all other variables and quotes.
	variables can become more than one word, but quotes has to stay together

	after quotes and variables have been resolved, we copy all words from the list
	into the final array for this pipe section.
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
		// here cursor points to the end of the section. can be a pipe or the end of the line
		ret = add_pipe_section(ret, duplicate_part_of_str(line, cursor - 1)); // we don't send the pipe symbol itself, or the \0
		if (*cursor) // if cursor is on a pipe symbol, we go to the next char for the next loop, otherwise we stay at 0 and we exit the loop
			cursor++;
		line = cursor;
	}
	return (ret);
}






t_lst_cmd	*free_lst_cmd(t_lst_cmd *list)
{
	t_lst_cmd	*temp;

	while (list)
	{
		free_array_of_string(list->arg);
//		free(list->command);
		free(list->inf);
		free(list->outf);
		temp = list->next;
		free(list);
		list = temp;
	}
	return (NULL);
}
