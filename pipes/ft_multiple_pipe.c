/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:20:06 by adidion           #+#    #+#             */
/*   Updated: 2021/12/04 15:11:34 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_multiple_pipe(t_lst_cmd *cmd, char ***env)
{
	int	fd[2];
	int	pid;
	int	fd2;
	int	r;
	int status = 0;

	fd2 = 0;
	r = 0;
	signal(SIGQUIT, ctrl_backslash_status_to_131);
	signal(SIGINT, ctrl_c_status_to_130); ////////////////////
	while (cmd)
	{
		if (status == 256)
			break ;
		pipe(fd);
		pid = fork();
		if (pid < 0)
			return (0);
		else if (pid == 0)
		{
			signal(SIGQUIT, ctrl_backslash_inside);
			signal(SIGINT, ctrl_c_status_to_130); //////////////////////
			dup2(fd2, 0);
			if (cmd->next)
				dup2(fd[1], 1);
			close(fd[0]);
			r = ft_verify_redi_2(*cmd, env);
//			close(fd[1]);
			exit(1);
		}
		else
		{
			waitpid(pid, &status, 0);
			set_signal(); ///////////////
			close(fd[1]);
			fd2 = fd[0];
			cmd = cmd->next;
		}
	}
	return (r);
}
