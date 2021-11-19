/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:35:03 by adidion           #+#    #+#             */
/*   Updated: 2021/11/19 17:24:14 by adidion          ###   ########.fr       */
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
	int		i;

	i = -1;
	if (!arg[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	while (arg[++i])
	{
		if (i > 0 && ft_strlen(arg[i]) == 0)
		{
			printf(" ");
			continue ;
		}
		else if (ft_verify_arg_2(arg[i]) == 1)
			bool = 1;
		else
			printf("%s", arg[i]);
	}
	if (bool == 0)
		printf("\n");
	return (0);
}
