/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:00:02 by adidion           #+#    #+#             */
/*   Updated: 2021/10/29 16:55:07 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	si bool == 0, pas d'arguments apres pwd
	si bool == 1, des arguments invalides
	
	si ce sont arguments valides qu'on ne doit pas gerer (-P, -L),
	il faut envoyer le tout dans une autre fct, pas ici
*/

int	ft_pwd(int bool)
{
	char	*pwd;

	if (bool == 1)
		return (1);
	pwd = getenv("PWD");
	if (!pwd)
		return (1);
	printf("%s\n", pwd);
	return (0);
}
