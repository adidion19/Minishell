/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:14 by ybrutout          #+#    #+#             */
/*   Updated: 2021/11/23 11:59:33 by ybrutout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(int signum)
{
	if (signum != SIGINT)
		return ;
	global.status = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_d(int signum)
{
	if (signum == SIGQUIT)
		return ;
	printf("je suis la\n");
	exit(EXIT_FAILURE);
}

void	set_signal(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_d);
}

int		main(void)
{
	global.status = 0;
	global.env = NULL;
	set_signal();
	while (1)
	{
		readline("essais>");
		write(1, "holla\n", 6);
		sleep(1);
	}
	return (0);
}
