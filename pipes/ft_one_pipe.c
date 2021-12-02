/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:30:23 by adidion           #+#    #+#             */
/*   Updated: 2021/12/02 14:40:56 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_one_pipe(t_lst_cmd *cmd, char ***env)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	status;
	int	r;

	r = 0;
	if (pipe(fd) == -1)
		return (127);
	pid1 = fork();
	if (pid1 < 0)
		return (127);
	if (pid1 == 0)
	{
		if (cmd->heredoc)
			dup2(fd[1], ft_heredoc(*cmd));
		//else
		dup2(fd[1], STDOUT_FILENO);
		ft_verify_redi_2(*cmd, env);
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	//close (fd[0]);
	waitpid(pid1, &status, 0);
	pid2 = fork();
	if (pid2 < 0)
		return (127);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		//close(fd[1]);
		r = ft_verify_redi_2(*cmd->next, env);
		close(fd[0]);
		exit(0);
	}
	waitpid(pid2, &status, 0);
	return (r);
}
