/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_in_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:49:22 by artmende          #+#    #+#             */
/*   Updated: 2021/12/10 19:27:41 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_signal_inside(t_lst_cmd *cmd)
{
	t_lst_cmd	*cmd_temp;

	cmd_temp = cmd;
	while (cmd_temp)
	{
		if (cmd_temp->heredoc == 1)
		{
			set_signal_inside_cmd_is_running_heredoc();
			return (1);
		}
		cmd_temp = cmd_temp->next;
	}
	set_signal_inside_cmd_is_running_no_heredoc();
	return (1);
}

int	set_signal_outside(t_lst_cmd *cmd)
{
	t_lst_cmd	*cmd_temp;

	cmd_temp = cmd;
	while (cmd_temp)
	{
		if (cmd_temp->heredoc == 1)
		{
			set_signal_outside_cmd_is_running_heredoc();
			return (1);
		}
		cmd_temp = cmd_temp->next;
	}
	set_signal_outside_cmd_is_running_no_heredoc();
	return (1);
}
