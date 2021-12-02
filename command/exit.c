/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:39:17 by adidion           #+#    #+#             */
/*   Updated: 2021/12/02 11:11:03 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_t_exit(int num, int bool, char *arg)
{
	printf("exit\n");
	if (bool)
	{
		write(2, "minishell: exit: ", 17);
		write(2, arg, ft_strlen(arg));
		write(2, ": numeric argument required\n", 28);
	}
	exit(num);
}

int	ft_is_alnum(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i] && arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (1);
	}
	return (0);
}

void	ft_verify_arg(char *arg)
{
	if (ft_is_alnum(arg))
	{
		ft_t_exit(255, 1, arg);
	}
}

int	ft_arg_len(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		;
	if (i > 1)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	return (0);
}

int	ft_exit(char **arg)
{
	unsigned long	i;

	if (!arg[0])
		exit(0);
		if (ft_arg_len(arg))
			return (1);
		ft_verify_arg(arg[0]);
		if (arg[0])
		{
			i = ft_strtol(arg[0]);
			i = (unsigned char) i;
			ft_t_exit(i, 0, NULL);
		}
	return (0);
}
