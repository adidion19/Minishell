/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:20:06 by adidion           #+#    #+#             */
/*   Updated: 2021/12/07 16:48:20 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_multiple_pipe(t_lst_cmd *cmd, char ***env)
{
	int	fd[2];
	pid_t	pid;
	pid_t	pid2;
	int		status;
	int	fd2;
	int	r;

	fd2 = 0;
	r = 0;
	while (cmd)
	{
		pipe(fd);
		pid = fork();
		if (pid < 0)
			return (0);
		else if (pid == 0)
		{
			if (cmd->heredoc)
				dup2(fd[1], ft_heredoc(*cmd));
			else
				dup2(fd2, 0);
			close(fd[0]);
			if (cmd->next)
				dup2(fd[1], 1);
			close(fd[1]);
			//signal(SIGKILL, NULL);
			r = ft_verify_redi_2(*cmd, env);
			exit(1);
		}
		else
		{
			close(fd[1]);
			close(fd[0]);
			fd2 = fd[0];
			cmd = cmd->next;
		}
	}
	close(fd[0]);
	while ((pid2 = waitpid(pid, &status, WNOHANG)) > 0)
	{
		;
	}
	//if (pid2 <= 0)
	//	exit(EXIT_FAILURE);
	return (r);
}
