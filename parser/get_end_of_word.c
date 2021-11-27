/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_end_of_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:19:01 by artmende          #+#    #+#             */
/*   Updated: 2021/11/27 14:33:48 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

/*
	A word is defined as characters separated by unquoted spaces.
	It can also be separated by begining and end of the string.
	It can be 1 char long.
	get_end_of_word returns the address of the last char of the word.
*/

char	*get_end_of_word(char *str)
{
	t_quote_state	quote;

	if (!str)
		return (NULL);
	if (*str == 0)
		return (str);
	ft_memset(&quote, 0, sizeof(quote));
	while (*str)
	{
		update_quote_state(str, &quote);
		if (quote.global_quote == 0 && ft_isspace(*str) == 1)
			break ;
		str++;
	}
	// str points to after the word. can be a space or can be \0
	return (str - 1);
}
