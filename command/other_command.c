/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:33:07 by adidion           #+#    #+#             */
/*   Updated: 2021/11/23 15:53:18 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error_other_command(char *cmd, int bool)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	if (bool == 1)
		write(2, ": No such file or directory\n", 29);
	if (bool == 0)
		write(2, ": command not found\n", 21);
	return (127);
}

char	**ft_find_path(char **env)
{
	int		i;
	char	**path;

	i = -1;
	while (env[++i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		;
	path = ft_split((env[i]) + 5, ':');
	return (path);
}

void	ft_free_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

/*
**	j'devrai peut etre modif dans mon execve les "cmd.arg"
	parce que j'aurai besoin de la commande en index 0
**	je dois aussi tester le cas ou l'on m'export un path random, et que le fichier
	n existe pas
*/

int	ft_other_command(t_lst_cmd cmd, char **env)
{
	int		i;
	char	**path;
	int		access;
	pid_t	pid;
	int		exit_status;
	int		status;

	i = -1;
	access = 0;
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		if (!env)
			return (ft_error_other_command(cmd.command, 1));
		path = ft_find_path(env);
		if (!path)
			return (ft_error_other_command(cmd.command, 1));
		while (path[++i])
		{
			path[i] = ft_strjoin_2(path[i], "/", 0);
			path[i] = ft_strjoin_2(path[i], cmd.arg[0], 1);
			if (execve(path[i], cmd.arg, env) == -1)
				access++;
		}
		ft_free_path(path);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	if (i == access)
		return (ft_error_other_command(cmd.command, 0));
	return (exit_status);
}
