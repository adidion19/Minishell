/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_debug_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 13:42:36 by artmende          #+#    #+#             */
/*   Updated: 2021/12/01 13:58:18 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

void	display_words_list(t_words_list	*list)
{
	printf("Displaying words_list...\n");
	while (list)
	{
		printf("Word -> %s\n", list->word);
		list = list->next;
	}
	printf("Done !\n");
}

void	display_cmd_list(t_lst_cmd *lst)
{
	int	pipe_nbr;
	int	i;

	pipe_nbr = 0;
	while (lst)
	{
		printf("--------\n\nPipe %d :\nArgs array : \n", pipe_nbr);
		i = 0;
		while (lst->arg && lst->arg[i])
		{
			printf("\t%s\n", lst->arg[i]);
			i++;
		}
		printf("\n");
		if (lst->heredoc)
			printf("heredoc --> %s\n", lst->inf);
		else
			printf("infile --> %s\n", lst->inf);
		if (lst->append)
			printf("outfile (append) --> %s\n", lst->outf);
		else
			printf("outfile (no append) --> %s\n", lst->outf);
		pipe_nbr++;
		lst = lst->next;
	}
}
