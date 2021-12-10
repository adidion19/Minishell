/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers_no_heredoc.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:11:46 by artmende          #+#    #+#             */
/*   Updated: 2021/12/10 19:27:35 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c_outside_no_heredoc(int sig)
{
	(void)sig;
	write(2, "\n", 1);
}

void	ctrl_backslash_outside_no_heredoc(int sig)
{
	(void)sig;
	write(2, "Quit: 3\n", 8);
}

void	ctrl_c_inside_no_heredoc(int sig)
{
	(void)sig;
	exit(130);
}

void	ctrl_backslash_inside_no_heredoc(int sig)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	exit(131);
	(void)sig;
}
