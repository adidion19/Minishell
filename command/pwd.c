/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:09:14 by ybrutout          #+#    #+#             */
/*   Updated: 2021/12/09 10:35:52 by artmende         ###   ########.fr       */
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

int	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if (!getcwd(pwd, PATH_MAX))
		return (1);
	printf("%s\n", pwd);
	return (0);
}
