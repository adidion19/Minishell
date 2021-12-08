/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:04:56 by artmende          #+#    #+#             */
/*   Updated: 2021/12/08 17:04:43 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int	display_syntax_error(char c)
{
	write(2, "exotic_shell: syntax error near unexpected token `", 50);
	write(2, &c, 1);
	write(2, "'\n", 2);
	return (0);
}

int	display_ambiguous_redirect(t_lst_cmd *cmd_node, char *var_name)
{
	cmd_node->delete_this_node = 1;
	write(2, "exotic_shell: $", 15);
	write(2, var_name, ft_strlen(var_name));
	write(2, ": ambiguous redirect\n", 21);
	return (0);
}
