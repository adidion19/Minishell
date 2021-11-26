/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:52:06 by adidion           #+#    #+#             */
/*   Updated: 2021/11/26 15:35:09 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error_dup(int error)
{
	write(2, "minishell: ", 11);
	write(2, strerror(error), ft_strlen(strerror(error)));
	write(2, "\n", 1);
	return (1);
}

int	ft_heredoc(t_lst_cmd cmd, char **env)
{
	int		pid1;
	char	*line;
	int		fd[2];
	int		r;
	int		status;

	r = 0;
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	line = NULL;
	if (pid1 < 0)
		return (0);
	if (pid1 == 0)
	{
		while (ft_strncmp(line, cmd.inf, ft_strlen(cmd.inf))
			|| ft_strlen(line) != ft_strlen(cmd.inf))
		{
			free(line);
			write(fd[1], line, ft_strlen(line));
			if (line != NULL)
				write(fd[1], "\n", 1);
			line = readline("> ");
		}
		free(line);
		close(fd[1]);
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid1, &status, 0);
	close(fd[1]);
	errno = 0;
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (ft_error_dup(errno));
	r = ft_other_command(cmd, env);
	close(fd[0]);
	return (r);
}
