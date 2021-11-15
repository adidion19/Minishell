/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:35:03 by adidion           #+#    #+#             */
/*   Updated: 2021/11/15 15:29:31 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	arg : tous les arg venant apres le echo ou le -n, si il y'en a un
**	env : l'env
**	bool : 0 si pas de -n, 1 si il existe
**	/!\ ne pas envoyer ici si d'autres options que -n
*/

int	ft_echo(char **arg, char **env, int bool)
{
	int		i;
	char	*str;

	i = -1;
	if (!arg)
	{
		if (bool == 0)
			write(1, "\n", 1);
		return (0);
	}
	while (arg[++i])
	{
		if (i != 0)
			printf(" ");
		if (arg[i][0] == '$' && ft_strlen(arg[i]) > 1)
		{
			str = ft_strjoin(arg[i] + 1, "=");
			printf("%s", env_find_the(str, env));
			free(str);
		}
		else
			printf("%s", arg[i]);
	}
	if (bool == 0)
		printf("\n");
	return (0);
}
