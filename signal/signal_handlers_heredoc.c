/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:18:15 by artmende          #+#    #+#             */
/*   Updated: 2021/12/10 19:27:40 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c_outside_heredoc(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	g_global.status = 1;
	g_global.start = 1;
}

void	ctrl_backslash_outside_heredoc(int sig)
{
	(void)sig;
	g_global.status = 0;
}

void	ctrl_c_inside_heredoc(int sig)
{
	(void)sig;
	exit(1);
}

void	ctrl_backslash_inside_heredoc(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}
