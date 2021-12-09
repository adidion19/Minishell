/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:20:06 by adidion           #+#    #+#             */
/*   Updated: 2021/12/09 16:26:00 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child(t_lst_cmd *cmd, int *fd, char ***env, int fd2)
{
	if (cmd->heredoc)
		dup2(fd[0], ft_heredoc(*cmd));
	else
		dup2(fd2, 0);
	close(fd[0]);
	if (cmd->next)
		dup2(fd[1], 1);
	g_global.status = ft_verify_redi_2(*cmd, env);
	exit(g_global.status);
}

int	ft_parent(t_lst_cmd *cmd, pid_t pid, int *fd, int fd2)
{
	int	i;
	int	status;

	i = -1;
	if (cmd->heredoc)
	{
		waitpid(pid, &status, 0);
		if (!cmd->next)
			return (0);
	}
	close(fd[1]);
	fd2 = fd[0];
	return (fd2);
}

int	close_all(pid_t pid, int i, int *fd)
{
	int	status;
	int	pid2;

	pid2 = waitpid(-1, &status, 0);
	while (pid2 > 0)
	{
		if (pid2 == pid)
		{
			while (i--)
				close(fd[i]);
			if (WIFEXITED(status))
			g_global.status = WEXITSTATUS(status);
		}
		pid2 = waitpid(-1, &status, 0);
	}
	free(fd);
	return (0);
}

int	ft_loop_pipe(t_lst_cmd *cmd, int *fd, int fd2, char ***env)
{
	int	i;
	int	pid;

	i = 0;
	while (cmd)
	{
		if (pipe(&fd[i]) < 0)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid < 0)
			return (0);
		else if (pid == 0)
			ft_child(cmd, fd + i, env, fd2);
		else
		{
			fd2 = ft_parent(cmd, pid, fd + i, fd2);
			if (!fd2)
				return (close_all(pid, i, fd));
			cmd = cmd->next;
			i += 2;
		}
	}
	return (close_all(pid, i, fd));
}

int	ft_multiple_pipe(t_lst_cmd *cmd, char ***env)
{
	int		*fd;
	int		fd2;

	fd = malloc(sizeof(int) * (2 * ft_lstsize(cmd)));
	if (!fd)
		exit(EXIT_FAILURE);
	fd2 = 50;
	return (ft_loop_pipe(cmd, fd, fd2, env));
}
