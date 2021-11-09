/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:05:18 by adidion           #+#    #+#             */
/*   Updated: 2021/11/09 14:50:21 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == '\n' || c == ' ' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

long	ft_return_of_strtol(int neg)
{
	if (neg > 0)
		return (-1);
	else
		return (0);
}

long	ft_strtol(const char *str)
{
	unsigned long long	i;
	long long			ans;
	int					neg;
	int					j;

	i = 0;
	ans = 0;
	neg = 1;
	j = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		((str[i] == '-') && (neg = neg * -1));
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ans = ans * 10 + str[i++] - '0';
		j++;
	}
	if (ans < 0 || j > 19)
		return (ft_return_of_strtol(neg));
	ans = ans * neg;
	return ((long)ans);
}

int	ft_atoi(const char *str)
{
	long long	i;

	i = ft_strtol(str);
	return ((int)i);
}
