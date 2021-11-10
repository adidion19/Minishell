/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:39:17 by adidion           #+#    #+#             */
/*   Updated: 2021/11/10 14:01:04 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_t_exit(int num, int bool, char *arg)
{
	printf("exit\n");
	if (bool)
		printf("bash: exit: %s: numeric argument required\n", arg);
	exit(num);
}

int	ft_is_alnum(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (!(arg[i] >= 0 && arg[i] <= 9))
			return (1);
	}
	return (0);
}

int	ft_verify_arg(char *arg)
{
	if (ft_is_alnum(arg))
	{
		ft_t_exit(255, 1, arg);
	}
	return (0);
}

int	ft_arg_len(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		;
	if (i > 1)
	{
		printf("exit: too many arguments");
		return (1);
	}
	return (0);
}

int	ft_exit(char **arg)
{
	unsigned long	i;

	if (arg)
	{
		if (ft_arg_len(arg))
			return (1);
		if (arg[0])
		{
			i = ft_strtol(arg[0]);
			i = (unsigned char) i;
			ft_t_exit(i, 0, NULL);
		}
	}
	else
		ft_t_exit(EXIT_SUCCESS, 0, NULL);
	return (0);
}
