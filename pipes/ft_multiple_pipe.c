/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:20:06 by adidion           #+#    #+#             */
/*   Updated: 2021/12/04 14:41:19 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_multiple_pipe(t_lst_cmd *cmd, char ***env)
{
	int	fd[2];
	int	pid;
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
			dup2(fd2, 0);
			if (cmd->next)
				dup2(fd[1], 1);
			close(fd[0]);
			r = ft_verify_redi_2(*cmd, env);
			exit(1);
		}
		else
		{
			waitpid(pid, 0, 0);
			close(fd[1]);
			fd2 = fd[0];
			cmd = cmd->next;
		}
	}
	return (r);
}
