/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multiple_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:20:06 by adidion           #+#    #+#             */
/*   Updated: 2021/12/08 11:17:45 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_lstsize(t_lst_cmd *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	ft_multiple_pipe(t_lst_cmd *cmd, char ***env)
{
	int	*fd;
	pid_t	pid;
	pid_t	pid2;
	int		status;
	int	fd2;
	int i;

	fd = malloc(sizeof(int) * (2 * ft_lstsize(cmd)));
	fd2 = 50;
	i = 0;
	while (cmd)
	{
		pipe(&fd[i]);
		pid = fork();
		if (pid < 0)
			return (0);
		else if (pid == 0)
		{
			if (cmd->heredoc)
				dup2(fd[i], ft_heredoc(*cmd));
			else
				dup2(fd2, 0);
			close(fd[i]);
			if (cmd->next)
				dup2(fd[i + 1], 1);
			g_global.status = ft_verify_redi_2(*cmd, env);
			exit(g_global.status);
		}
		else
		{
			if (cmd->heredoc)
				waitpid(pid, &status, 0);
			close(fd[i + 1]);
			fd2 = fd[i];
			cmd = cmd->next;
			i += 2;
		}
	}
	while ((pid2 = waitpid(-1, &status, 0)) > 0)
	{
		if (pid2 == pid)
		{
			while (i--)
				close(fd[i]);
			if (WIFEXITED(status))
				g_global.status = WEXITSTATUS(status);
		}
	}
	free(fd);
	return (status);
}
