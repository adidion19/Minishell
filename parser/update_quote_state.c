/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_quote_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:04:31 by artmende          #+#    #+#             */
/*   Updated: 2021/11/23 15:55:18 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

int	update_quote_state(char *str, t_quote_state *state)
{
	if (*str == '\'')
	{
		if (state->global_quote == 0 && ft_strchr(str + 1, '\''))
		{
			state->simple_quote = 1;
			state->global_quote = 1;
		}
		else if (state->simple_quote != 0)
			ft_memset(state, 0, sizeof(t_quote_state));
	}
	if (*str == '"')
	{
		if (state->global_quote == 0 && ft_strchr(str + 1, '"'))
		{
			state->double_quote = 1;
			state->global_quote = 1;
		}
		else if (state->double_quote != 0)
			ft_memset(state, 0, sizeof(t_quote_state));
	}
	return (1);
}
