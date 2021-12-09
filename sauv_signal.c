/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sauv_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:14 by ybrutout          #+#    #+#             */
/*   Updated: 2021/12/09 19:43:18 by artmende         ###   ########.fr       */
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

int	set_signal_default(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_backslash_default);
	return (1);
}

void	set_signal_outside_cmd_is_running(void)
{
	signal(SIGQUIT, ctrl_backslash_outside_no_heredoc);
	signal(SIGINT, ctrl_c_outside_no_heredoc);
}

void	set_signal_inside_cmd_is_running(void)
{
	signal(SIGQUIT, ctrl_backslash_inside);
	signal(SIGINT, ctrl_c_inside);
}


void	ctrl_c_outside_no_heredoc(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	g_global.status = 130;
}

void	ctrl_c_status_to_1(int sig)
{
	// use if there is heredoc
	(void)sig;
	write(2, "\n", 1);
	g_global.status = 1;
}

void	ctrl_backslash_outside_no_heredoc(int sig)
{
	(void)sig;
	write(2, "Quit: 3\n", 8);
	g_global.status = 131;
}

void	ctrl_backslash_status_to_0(int sig)
{
	// use if there is heredoc
	(void)sig;
	g_global.status = 0;
}

void	sig_do_nothing(int sig)
{
	(void)sig;
}

void	ctrl_backslash_default(int sig)
{
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}


void	ctrl_backslash_inside(int sig)
{
//	write(2, "Quit: 3\n", 8);
	rl_replace_line("", 0);
	rl_on_new_line();
//	printf("inside sig : global is %d\n", g_global.status);
	exit(131);
	(void)sig;
}

void	ctrl_c_inside(int sig)
{
	(void)sig;
	exit(130);
}


void	call_exit_from_signal(int sig)
{
	(void)sig;
	exit(EXIT_FAILURE);
}








