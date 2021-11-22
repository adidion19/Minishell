/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:00:02 by adidion           #+#    #+#             */
/*   Updated: 2021/11/22 15:58:52 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	va chercher et imprime la valeur du pwd actuel.
**	/!\ si arguments apres PWD :
	-L -> a envoyer ici
	-P -> a envoyer sur un execve
	-quelqueChoseDAutre -> pwd: bad option: -quelqueChoseDAutre -> exit(1)
	autre chose : pwd: too many arguments -> exit(1)
*/

int	ft_pwd(char **env)
{
	int		i;
	char	pwd[PATH_MAX];

	i = -1;
	if (!getcwd(pwd, PATH_MAX))
		return (1);
	printf("%s\n", pwd);
	return (0);
}
