/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:52:06 by adidion           #+#    #+#             */
/*   Updated: 2021/11/24 17:55:44 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc(t_lst_cmd cmd, char **env)
{
	int		pid1;
	int		pid2;
	char	*line;
	int		fd[2];
	int		r;
	int		status;

	r = 0;
	if (pipe(fd))
		exit(EXIT_FAILURE);
	pid1 = fork();
	line = NULL;
	if (pid1 < 0)
		return (0);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		while (!ft_strncmp(line, cmd.inf, ft_strlen(cmd.inf)))
		{
			line = readline("> ");
			write(fd[1], line, ft_strlen(line));
		}
	}
	pid2 = fork();
	if (pid2 < 0)
		return (0);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		r = ft_choose_command(cmd, &env);
	}
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (r);
}
