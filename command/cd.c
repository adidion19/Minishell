/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:08:33 by ybrutout          #+#    #+#             */
/*   Updated: 2021/11/25 15:08:09 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	update du oldpwd
** ! il faudra peut etre free des trucs, a voir plus tard
*/

char	*ft_update_oldpwd(char *pwd, char *oldpwd_2)
{
	char	*oldpwd;

	oldpwd = ft_strdup(pwd);
	if (!oldpwd)
		exit(EXIT_FAILURE);
	free(oldpwd_2);
	return (oldpwd);
}

/*
**	update du pwd
** ! il faudra peut etre free des trucs, a voir plus tard
*/

char	*ft_update_pwd(char *pwd_2)
{
	char	*pwd;
	char	buff[PATH_MAX];

	getcwd(buff, PATH_MAX);
	pwd = ft_strdup(buff);
	if (!pwd)
		exit(EXIT_FAILURE);
	free(pwd_2);
	return (pwd);
}

void	ft_error_cd(char *path)
{
	write(2, "minishell: cd: ", 15);
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
}

int	ft_error(char *path, int error)
{
	ft_error_cd(path);
	write(2, strerror(error), ft_strlen(strerror(error)));
	write(2, "\n", 1);
	return (1);
}

/*
**	path : le path (relati ou absolu)
**	oldpwd : le oldpwd de l'env copiee dereference pour le
		modifier sans le retourner
**	oldpwd : le oldpwd de l'env copiee dereference pour le
		modifier sans le retourner
**	retourne 1 en cas d'erreur et 0 si reussi (exit status)
*/

int	ft_cd(char *path, char **pwd, char **oldpwd, char **env)
{
	int	error;

	errno = 0;
	if (!path)
		path = env_find_the("HOME=", env);
	if (path[0] == '\0')
		return (0);
	if (chdir(path) == -1)
	{
		error = errno;
		return (ft_error(path, error));
	}
	*oldpwd = ft_update_oldpwd(*pwd, *oldpwd);
	*pwd = ft_update_pwd(*pwd);
	return (0);
}
