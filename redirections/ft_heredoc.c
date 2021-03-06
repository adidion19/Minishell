/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:52:06 by adidion           #+#    #+#             */
/*   Updated: 2021/12/11 12:54:34 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error_dup(int error)
{
	write(2, "exotic_shell: ", 14);
	write(2, strerror(error), ft_strlen(strerror(error)));
	write(2, "\n", 1);
	return (1);
}

char	*ft_loop_heredoc(char *line2, int fd)
{
	if (line2 != NULL)
	{
		write(fd, line2, ft_strlen(line2));
		write(fd, "\n", 1);
	}
	free(line2);
	line2 = readline("> ");
	if (!line2)
		exit(0);
	return (line2);
}

int	ft_close_and_free(char *line2, int *fd)
{
	free(line2);
	close(fd[1]);
	close(fd[0]);
	return (0);
}

int	ft_heredoc(t_lst_cmd cmd)
{
	int		pid1;
	char	*line2;
	int		fd[2];
	int		status;

	neg(pipe(fd));
	line2 = NULL;
	pid1 = fork();
	neg(pid1);
	if (pid1 == 0 && set_signal_inside_cmd_is_running_heredoc())
		while (ft_strncmp(line2, cmd.inf, ft_strlen(cmd.inf))
			|| ft_strlen(line2) != ft_strlen(cmd.inf))
			line2 = ft_loop_heredoc(line2, fd[1]);
	if (pid1 == 0)
		exit(ft_close_and_free(line2, fd));
	if (pid1 > 0)
		signal(SIGQUIT, sig_do_nothing);
	waitpid(pid1, &status, 0);
	set_signal_inside_cmd_is_running_heredoc();
	close(fd[1]);
	errno = 0;
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit(ft_error_dup(errno));
	close (fd[0]);
	return (fd[1]);
}
