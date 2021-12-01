/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pipe_section.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:04:11 by artmende          #+#    #+#             */
/*   Updated: 2021/12/01 18:04:47 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

/*
	add_pipe_section :

	First we create the words list.
	It's a linked list of all the words of that pipe section.
	A word is defined as a group of chars separated by unquoted white spaces,
	or by the beginning/end of the string.

	It means that whatever is between quotes is indivisible and stays together.

	Secondly we get the (in/out)files, and we delete the corresponding nodes
	from the words list.

	All words that remain in the words list at this point are the command, and
	its arguments.

	We expand the environment variables in the list, and if a variable contains
	more than one word, we separate them and add new nodes in words_list.

	At this point, all that is left to do is to copy all words from the list
	into an array of string that will be kept in the command list.
	We remove quotes from words at that final stage.
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
