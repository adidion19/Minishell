/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:35:03 by adidion           #+#    #+#             */
/*   Updated: 2021/11/30 15:02:06 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	arg : tous les arg venant apres le echo ou le -n, si il y'en a un
**	env : l'env
**	bool : 0 si pas de -n, 1 si il existe
**	/!\ ne pas envoyer ici si d'autres options que -n
*/

int	ft_verify_arg_2(char *arg)
{
	int	i;

	if (ft_strlen(arg) < 2)
		return (0);
	i = -1;
	if (arg[++i] != '-')
		return (0);
	while (arg[++i] && arg[i] == 'n')
		;
	if (arg[i] == '\0')
		return (1);
	else
		return (0);
}

int	ft_echo(char **arg, int bool)
{
	int	i;
	int	bool2;
	int	j;

	i = -1;
	j = -50;
	bool2 = 0;
	while (arg[0] && arg[++i])
	{
		if (bool2 == 0 && ft_verify_arg_2(arg[i]) == 1)
		{
			j = i;
			bool = 1;
		}
		else
		{
			bool2 = 1;
			if (i != 0 && i != (j + 1))
				printf(" ");
			printf("%s", arg[i]);
		}
	}
	if (!arg[0] || bool == 0)
		printf("\n");
	return (0);
}
