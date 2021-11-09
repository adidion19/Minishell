/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:48:13 by adidion           #+#    #+#             */
/*   Updated: 2021/11/09 16:08:49 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	imprime le tableau d'environnement en entier.
*/

int	ft_env(char **env)
{
	int		i;

	if (!env)
		return (1);
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	return (0);
}
