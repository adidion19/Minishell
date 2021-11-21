/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:48:13 by adidion           #+#    #+#             */
/*   Updated: 2021/11/21 12:10:33 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	imprime le tableau d'environnement en entier.
**	/!\ ne surtout pas envoyer env ici si il est suivi d'arguments (que ce soit
**		fichier valides ou non)
*/

int	ft_env(t_lst_cmd cmd, char **env)
{
	int	i;
	int	len;

	if (!env)
		return (1);
	if (cmd.arg[1])
	{
		write(2, "too much arguments for this command\n", 36);
		return (1);
	}
	i = 0;
	len = len_lst(env);
	while (i < len)
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
