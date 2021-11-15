/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_quote_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:04:31 by artmende          #+#    #+#             */
/*   Updated: 2021/11/15 15:04:43 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

void	update_quote_state(char c, t_quote_state *state)
{
	if (c == '\'')
	{
		if (state->global_quote == 0)
		{
			state->simple_quote = 1;
			state->global_quote = 1;
		}
		else if (state->simple_quote != 0)
			ft_memset(state, 0, sizeof(t_quote_state));
	}
	if (c == '"')
	{
		if (state->global_quote == 0)
		{
			state->double_quote = 1;
			state->global_quote = 1;
		}
		else if (state->double_quote != 0)
			ft_memset(state, 0, sizeof(t_quote_state));
	}
}
