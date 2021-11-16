/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:07:27 by artmende          #+#    #+#             */
/*   Updated: 2021/11/16 16:54:08 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

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

void	extract_input(t_lst_cmd *node, char *str)
{
	// for now it will remain 0
/* 
	t_quote_state	quote;

//	node->input_fd = DEFAULT_VALUE; // input_str can remain NULL
	ft_memset(&quote, 0, sizeof(quote));
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




t_lst_cmd	*add_pipe_section(t_lst_cmd *list, char *str)
{
	t_lst_cmd	*ret;
	t_lst_cmd	*temp;

	ret = ft_calloc(sizeof(t_lst_cmd));
	if (!ret)
		return (list); // in case allocation fail, we still have to return previous nodes to be able to free them
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

void	free_str_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = 0;
		i++;
	}
	free(array);
}

t_lst_cmd	*free_lst_cmd(t_lst_cmd *list)
{
	t_lst_cmd	*temp;

	while (list)
	{
		free_str_array(list->command);
		free(list->command);
		free(list->inf);
		free(list->outf);
		temp = list->next;
		free(list);
		list = temp;
	}
	return (NULL);
}

char	*duplicate_part_of_str(char *from, char *to)
{
	int		i;
	char	*ret;

	ret = ft_calloc(sizeof(char) * ((to - from) + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	i = 0;
	while (from <= to)
	{
		ret[i] = *from;
		i++;
		from++;
	}
	return (ret);
}

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
			return (free_lst_cmd(ret)); // need to free the linked list
		
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
	if (argc > 1)
	{
		printf("\n%s\n\n", argv[1]);
//		parser(argv[1]);
	}
	return (0);
}
