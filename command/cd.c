/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:01:18 by adidion           #+#    #+#             */
/*   Updated: 2021/11/16 16:34:38 by adidion          ###   ########.fr       */
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

char	*ft_update_pwd(char *path, char *pwd_2)
{
	char	*pwd;

	pwd = ft_strdup(path);
	if (!pwd)
		exit(EXIT_FAILURE);
	free(pwd_2);
	return (pwd);
}

/*
**	cas d'erreurs
**	je dois encore gerer si le path existe mais que ce n'est pas un dir
*/

int	ft_error(char *path, int error)
{
	if (error == ENOENT)
		printf("minishell: cd: %s: No such file or directory\n", path);
	if (error == ENOTDIR)
		printf("minishell: cd: %s: Not a directory\n", path);
	if (error == ENAMETOOLONG)
		printf("minishell: cd: %s: File name too long\n", path);
	if (error == EACCES)
		printf("minishell: cd: %s: Permission denied\n", path);
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

int	ft_cd(char *path, char **pwd, char **oldpwd)
{
	int	error;

	errno = 0;
	if (!path)
		path = "~";
	if (!ft_strncmp("", path, 1))
		return (0);
	if (chdir(path) == -1)
	{
		error = errno;
		return (ft_error(path, error));
	}
	*oldpwd = ft_update_oldpwd(*pwd, *oldpwd);
	*pwd = ft_update_pwd(path, *pwd);
	return (0);
}