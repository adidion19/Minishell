/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:14 by ybrutout          #+#    #+#             */
/*   Updated: 2021/12/04 13:34:13 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(int signum)
{
	if (signum != SIGINT)
		return ;
	g_global.status = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_backslach(int signum)
{
	if (signum == SIGQUIT)
	{
		if (g_global.start)
		{
			//g_global.start = 0;
			write(2, "Quit: 3\n", 8);
		rl_on_new_line();
		rl_replace_line("", 0);
		//rl_redisplay();
		}
	}
}

void	set_signal(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_backslach);
}

void	ctrl_backslash_outside(int sig)
{
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_backslash_inside(int sig)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	(void)sig;
}

