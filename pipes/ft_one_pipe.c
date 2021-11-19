/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:30:23 by adidion           #+#    #+#             */
/*   Updated: 2021/11/19 13:47:59 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_one_pipe(t_lst_cmd *cmd, char **env)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	status;
	int	r;

	if (pipe(fd) == -1)
		return (127);
	pid1 = fork();
	if (pid1 < 0)
		return (127);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		ft_verify_redi(*cmd, env);
		close(fd[1]);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (127);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		r = ft_verify_redi(cmd->next, env);
		close(fd[0]);
	}
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (r);
}
