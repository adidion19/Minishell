/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:33:07 by adidion           #+#    #+#             */
/*   Updated: 2021/12/08 11:13:21 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (!env[i])
		return (0);
	path = ft_split((env[i]) + 5, ':');
	return (path);
}

/*
**	j'devrai peut etre modif dans mon execve les "cmd.arg"
	parce que j'aurai besoin de la commande en index 0
**	je dois aussi tester le cas ou l'on m'export un path random, et que le fichier
	n existe pas
*/

static int	return_of_execve(int status, t_lst_cmd cmd)
{
	int	exit_status;

	exit_status = 0;
	if (status == 768)
		return (ft_error_other_command(cmd.command, 0));
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	return (exit_status);
}

static int	ft_exec(char **path, t_lst_cmd cmd, char **env)
{
	int	i;
	int	j;

	i = -1;
	errno = 0;
	while (path[++i])
	{
		errno = 0;
		path[i] = ft_strjoin_2(path[i], "/", 0);
		path[i] = ft_strjoin_2(path[i], cmd.arg[0], 1);
		if (execve(path[i], cmd.arg, env) == -1)
			if (errno != ENOENT)
				return (errno);
	}
	j = -1;
	while (path[++j])
		free(path[j]);
	free(path);
	return (2);
}

void	testsigquit(int sig)
{
	(void)sig;
	printf("This is the child !\n");
}

int	ft_other_command(t_lst_cmd cmd, char **env)
{
	char	**path;
	pid_t	pid;
	int		status;
	int r;

	status = 0;
	r = 1;
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		if (!env)
			exit(ft_error_other_command(cmd.command, 1));
		if (execve(cmd.arg[0], cmd.arg, env) == -1)
			if (errno != ENOENT)
				return (r = errno + 1);
		path = ft_find_path(env);
		if (!path)
			exit(ft_error_other_command(cmd.command, 1));
			r = ft_exec(path, cmd, env);
		exit(r + 1);
	}
	pid = waitpid(pid, &status, 0);
	return (g_global.status = return_of_execve(status, cmd));
}
