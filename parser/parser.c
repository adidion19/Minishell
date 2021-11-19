/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:07:27 by artmende          #+#    #+#             */
/*   Updated: 2021/11/19 13:33:09 by artmende         ###   ########.fr       */
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
		update_quote_state(*str, &quote);
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
	
	extract_input(ret, str); // can have substitution in 3 cases
	extract_output(ret, str);
	extract_cmd_array(ret, str);
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
typedef struct s_lst_cmd
{
	char				*command;
	char				**arg; //arg[0] = nom de la commande
	char				*inf;
	char				*outf;
	int					infd;
	int					outfd;
	struct s_lst_cmd	*next;
}	t_lst_cmd;
 */




t_lst_cmd	*parser(char *line)
{
	t_lst_cmd		*ret;
	t_quote_state	quote;
	char			*cursor;

	if (!line)
		return (NULL);
	ft_memset(&quote, 0, sizeof(quote));
	ret = 0;
	cursor = line;
	while (*line)
	{
		// we keep browsing as long as we didnt find a | outside of quote
		// if we are in quote, we just browse
		// if we are not in quote, we look for |
		while (*cursor)
		{
			update_quote_state(*cursor, &quote);
			if (*cursor == '|' && quote.global_quote == 0)
				break ;
			cursor++;
		}
		// here cursor points to the end of the section. can be a pipe or the end of the line
		// verify that cursor and line are not the same.
		// if not the same, duplicate that section and call add_pipe with duplicated string
		// do't forget to free it afterwards
		if (cursor == line)
			return (free_lst_cmd(ret)); // need to free the linked list probably need to write some error message at that time
		
		ret = add_pipe_section(ret, duplicate_part_of_str(line, cursor));

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

/* 	
	if (argc > 1)
	{
		t_words_list	*list;

		list = 0;

		list = create_words_list(argv[1]);

		t_words_list	*temp = list;

		while (list)
		{
			printf("%s\n", list->word);
			list = list->next;
		}
		printf("\nStarting cleaning the list\n");

		free_word_list(temp, 1);

		printf("%s\n", getenv("YOUPLABOUM"));
	}

 */


	
	return (0);
}
