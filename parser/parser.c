/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:07:27 by artmende          #+#    #+#             */
/*   Updated: 2021/11/23 15:49:49 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"


/*  // this one probably no need
char	*copy_next_word(char *from, char **adrs_of_original_ptr)
{
	if (!from || *from != ' ')
		//SYNTAX ERROR ! We have a < that is followed by garbage value
	while (*from == ' ')
		from++;
	// we can have something like << or <> so still need to understand how to handle that

	// the idea is to allocate and copy what follows the '<' and substitute it with var and getenv if necessary
	// then update the adrs_of_original_ptr so that the main loop can continue
}
 */

char	*add_infile(t_lst_cmd *node, char *str)
{
	if (*str == '<')
	{
		// double redirection to the left
	}
	while (ft_isspace(*str))
		str++;
	
	return (0); ///////// remove that
}


void	extract_input(t_lst_cmd *node, char *str)
{
	t_quote_state	quote;

	ft_memset(&quote, 0, sizeof(quote));
	while (*str)
	{
		update_quote_state(str, &quote);
		if (*str == '<' && quote.global_quote == 0)
			str = add_infile(node, str + 1);
	}





/* 


//	node->input_fd = DEFAULT_VALUE; // input_str can remain NULL

	while (from && to && from < to) // pointer increases when we browse the str
	{
		update_quote_state(*from, &quote);
		if (*from == '<' && quote.global_quote == 0)
			node->inf = copy_next_word(from + 1, &from);
		from++;
	}
 */

}

void	extract_output(t_lst_cmd *node, char *str)
{

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
	// create linked list that contains all words
	words_list = create_words_list(str);
	
	words_list = get_input_output(ret, words_list);

	extract_input(ret, str);
	extract_output(ret, str);
//	handle_cmd_args_in_list(words_list);
	extract_cmd_array(ret, str);
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

	if (!line || !verify_pipe_conditions(line))
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



//	printf("%s\n", getenv("COUCOUU"));
	// getenv returns a null pointer when it didnt find the matching variable
/* 	int	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	} */


	if (argc < 2)
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
