/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:07:27 by artmende          #+#    #+#             */
/*   Updated: 2021/11/29 12:20:38 by user             ###   ########.fr       */
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
		// expand variables and remove quote (temp->word);
		node->arg[i] = temp->word;
		i++;
		temp = temp->next;
	}
	node->command = node->arg[0];
	free_words_list(words_list, 0);
}




/* 
	First we create the words list.
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
		free_words_list(list, 1);
		words_list = 0;
	}
	handle_cmd_args_in_list(ret, words_list);
//	extract_cmd_array(ret, str); // what if words_list has been freed ?
//	create_cmd_array(ret, words_list);
	ret->next = 0; // no need, it's already 0 by default
	// what if one extract fails ?
	free(str);
	if (!list)
		return (ret);
	temp = list;
	while (temp && temp->next)
		temp = temp->next;
	// temp points now to the last element of the list
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

int	main(int argc, char **argv, char **envp)
{



	printf("%s\n", getenv(0));
	// getenv returns a null pointer when it didnt find the matching variable
/* 	int	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	} */


	if (argc < 2)
		return (0);

		if (!verify_redirections(argv[1]))
			return (0);
		t_words_list	*list;

		list = 0;

		list = create_words_list(argv[1]);

	printf("\n\n");

		display_words_list(list);

//	list = split_words_with_redirection_symbols(list);



//	printf("\n\n");

//	display_words_list(list);

/* 

		printf("deleting element starting with 4 and 3... ");

		temp = list;
		while (temp)
		{
			if (temp->word[0] == '4')
				break ;
			temp = temp->next;
		}
		list = delete_node_words_list(list, temp);

		temp = list;
		while (temp)
		{
			if (temp->word[0] == '3')
				break ;
			temp = temp->next;
		}
		list = delete_node_words_list(list, temp);

		printf("done !\n");

		temp = list;
		while (temp)
		{
			printf("->%s\n", temp->word);
			temp = temp->next;
		}
 */

		printf("\nStarting cleaning the list\n");

		free_words_list(list, 1);

		printf("%s\n", getenv("YOUPLABOUM"));





	
	return (0);
}
