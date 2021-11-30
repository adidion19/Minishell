/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:52:06 by adidion           #+#    #+#             */
/*   Updated: 2021/11/30 12:42:33 by adidion          ###   ########.fr       */
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

static int	ft_error_other_command(char *cmd, int bool)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	if (bool == 1)
		write(2, ": No such file or directory\n", 29);
	if (bool == 0)
		write(2, ": command not found\n", 21);
	return (127);
}

static char	**ft_find_path(char **env)
{
	int		i;
	char	**path;

	i = -1;
	while (env[++i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		;
	path = ft_split((env[i]) + 5, ':');
	return (path);
}

/*
**	j'devrai peut etre modif dans mon execve les "cmd.arg"
	parce que j'aurai besoin de la commande en index 0
**	je dois aussi tester le cas ou l'on m'export un path random, et que le fichier
	n existe pas
*/

static int	return_of_execve(int i, int status, int access, t_lst_cmd cmd)
{
	int	exit_status;

	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	if (i + 1 == access)
		return (ft_error_other_command(cmd.command, 0));
	return (exit_status);
}

static int	ft_exec(char **path, t_lst_cmd cmd, int *access, char **env)
{
	int	i;
	int	j;

	i = -1;
	while (path[++i])
	{
		path[i] = ft_strjoin_2(path[i], "/", 0);
		path[i] = ft_strjoin_2(path[i], cmd.arg[0], 1);
		if (execve(path[i], cmd.arg, env) == -1)
			*access = *access + 1;
	}
	j = -1;
	while (path[++j])
		free(path[j]);
	free(path);
	return (i);
}

int	ft_other_command_2(t_lst_cmd cmd, char **env, int *fd)
{
	char	**path;
	int		access;
	pid_t	pid;
	int		status;
	int		i;

	access = 0;
	status = 0;
		//printf("A");
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		errno = 0;
		if (dup2(fd[0], STDIN_FILENO) == -1)
			exit(ft_error_dup(errno));
		if (!env)
			exit(ft_error_other_command(cmd.command, 1));
		if (execve(cmd.arg[0], cmd.arg, env) == -1)
			access++;
		path = ft_find_path(env);
		if (!path)
			exit(ft_error_other_command(cmd.command, 1));
		i = ft_exec(path, cmd, &access, env);
		if (close(fd[1] == -1 || close(fd[0]) == -1))
			exit(0);
		exit(i);
	}
	waitpid(pid, &status, 0);
	return (return_of_execve(i, status, access, cmd));
}

int	ft_heredoc(t_lst_cmd cmd, char **env)
{
	int		pid1;
//	int		 pid2;
	char	*line2;
	int		fd[2];
	int		r;
	int		status;
	char c;

	r = -1;
	status = 0;
	c = EOF;
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	line2 = NULL;
	pid1 = fork();
	if (pid1 < 0)
		return (-1);
	if (pid1 == 0)
	{
		while (ft_strncmp(line2, cmd.inf, ft_strlen(cmd.inf))
			|| ft_strlen(line2) != ft_strlen(cmd.inf))
		{
			if (line2 != NULL)
			{
				write(fd[1], line2, ft_strlen(line2));
				write(fd[1], "\n", 1);
			}
			free(line2);
			line2 = readline("> ");
		}
		free(line2);
		close(fd[1]);
		close(fd[0]);
		exit(0);
	}
	waitpid(pid1, &status, 0);
	close(fd[1]);
	r = ft_other_command_2(cmd, env, fd);
	return (r);
}
