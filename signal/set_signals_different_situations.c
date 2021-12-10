/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals_different_situations.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:52:16 by artmende          #+#    #+#             */
/*   Updated: 2021/12/10 19:27:43 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_signal_default(void)
{
	signal(SIGINT, ctrl_c_default);
	signal(SIGQUIT, ctrl_backslash_default);
	return (1);
}

int	set_signal_outside_cmd_is_running_no_heredoc(void)
{
	signal(SIGQUIT, ctrl_backslash_outside_no_heredoc);
	signal(SIGINT, ctrl_c_outside_no_heredoc);
	return (1);
}

int	set_signal_outside_cmd_is_running_heredoc(void)
{
	signal(SIGQUIT, ctrl_backslash_outside_heredoc);
	signal(SIGINT, ctrl_c_outside_heredoc);
	return (1);
}

int	set_signal_inside_cmd_is_running_no_heredoc(void)
{
	signal(SIGQUIT, ctrl_backslash_inside_no_heredoc);
	signal(SIGINT, ctrl_c_inside_no_heredoc);
	return (1);
}

int	set_signal_inside_cmd_is_running_heredoc(void)
{
	signal(SIGQUIT, ctrl_backslash_inside_heredoc);
	signal(SIGINT, ctrl_c_inside_heredoc);
	return (1);
}
