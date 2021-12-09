/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:14 by ybrutout          #+#    #+#             */
/*   Updated: 2021/12/09 11:32:56 by adidion          ###   ########.fr       */
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

/* void	ctrl_backslach(int signum)
{
	if (signum == SIGQUIT)
	{
		if (g_global.start)
		{
			//g_global.start = 0;
			write(2, "Quit: 3\n", 8);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		}
	}
} */

/* void ctrl_backslach(int signum)
{
	(void)signum;
	if (g_global.start == 1)
	{
		g_global.start--;
		return ;
	}
	if (g_global.start == 2)
	{
		write(2, "Quit: 3\n", 8);
		rl_replace_line("", 0);
		rl_on_new_line();
		return ;
	}
	if (g_global.start == 0)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
//	printf("PID is %d and ", getpid());
//	printf("this is parent\n");
} */

int	set_signal(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_backslash_outside);
	return (1);
}

void	ctrl_c_status_to_130(int sig)
{
	(void)sig;
	g_global.status = 130;
}

void	ctrl_backslash_status_to_131(int sig)
{
	(void)sig;
	g_global.status = 131;
}

void	ctrl_backslash_outside(int sig)
{
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}
