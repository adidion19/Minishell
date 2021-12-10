/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:14 by ybrutout          #+#    #+#             */
/*   Updated: 2021/12/10 11:57:19 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_signal_default(void)
{
	signal(SIGINT, ctrl_c_default);
	signal(SIGQUIT, ctrl_backslash_default);
	return (1);
}

void	set_signal_outside_cmd_is_running_no_heredoc(void)
{
	signal(SIGQUIT, ctrl_backslash_outside_no_heredoc);
	signal(SIGINT, ctrl_c_outside_no_heredoc);
}

void	set_signal_inside_cmd_is_running_no_heredoc(void)
{
	signal(SIGQUIT, ctrl_backslash_inside);
	signal(SIGINT, ctrl_c_inside_no_heredoc);
}

void	set_signal_heredoc_itself(void)
{
//	set_signal_inside_cmd_is_running_no_heredoc();
	set_signal_inside_cmd_is_running_heredoc();
//	signal(SIGQUIT, sig_do_nothing);
//	signal(SIGINT, call_exit_from_signal);
}

void	set_signal_inside_cmd_is_running_heredoc(void)
{
//	set_signal_inside_cmd_is_running_no_heredoc();
//	signal(SIGQUIT, call_exit_from_signal);
//	signal(SIGINT, ctrl_c_outside_no_heredoc);
	signal(SIGQUIT, ctrl_backslash_inside_heredoc);
	signal(SIGINT, ctrl_c_inside_heredoc);

}

void	set_signal_outside_cmd_is_running_heredoc(void)
{
	signal(SIGQUIT, ctrl_backslash_outside_heredoc);
	signal(SIGINT, ctrl_c_outside_no_heredoc);
}

void	set_signal_inside(t_lst_cmd *cmd)
{
	t_lst_cmd	*cmd_temp;

	cmd_temp = cmd;
	while (cmd_temp)
	{
		if (cmd_temp->heredoc == 1)
		{
			set_signal_inside_cmd_is_running_heredoc();
			return ;
		}
		cmd_temp = cmd_temp->next;
	}
	set_signal_inside_cmd_is_running_no_heredoc();
}

void	set_signal_outside(t_lst_cmd *cmd)
{
	t_lst_cmd	*cmd_temp;

	cmd_temp = cmd;
	while (cmd_temp)
	{
		if (cmd_temp->heredoc == 1)
		{
//			set_signal_default();
			set_signal_outside_cmd_is_running_heredoc();
			return ;
		}
		cmd_temp = cmd_temp->next;
	}
	set_signal_outside_cmd_is_running_no_heredoc();
}



void	ctrl_c_default(int signum)
{
	if (signum != SIGINT)
		return ;
	g_global.status = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}





void	ctrl_c_outside_no_heredoc(int sig)
{
	(void)sig;
	write(2, "\n", 1);
}

void	ctrl_backslash_outside_heredoc(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	g_global.status = 1;
}

void	ctrl_backslash_outside_no_heredoc(int sig)
{
	(void)sig;
	write(2, "Quit: 3\n", 8);
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

void	ctrl_backslash_inside_heredoc(int sig)
{
	// use if there is heredoc
	(void)sig;
	exit(0);
}

void	ctrl_backslash_inside(int sig)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	exit(131);
	(void)sig;
}

void	ctrl_c_inside_no_heredoc(int sig)
{
	(void)sig;
	exit(130);
}

void	ctrl_c_inside_heredoc(int sig)
{
//	printf("test\n");
	(void)sig;
	exit(1);
}

void	call_exit_from_signal(int sig)
{
	(void)sig;
	exit(EXIT_FAILURE);
}

