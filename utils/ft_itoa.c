/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:18:56 by adidion           #+#    #+#             */
/*   Updated: 2021/11/09 16:17:14 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	c;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	while (i < len / 2)
	{
		c = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = c;
		i++;
	}
	return (str);
}

int	len_of_int(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = n * -1;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	count++;
	return (count);
}

unsigned int	a_value_of_itoa(int n)
{
	unsigned int	a;

	if (n >= 0)
		a = n;
	else
		a = -n;
	return (a);
}

char	*ft_itoa(int n)
{
	char			*ans;
	int				bool_;
	unsigned int	a;
	int				i;

	bool_ = 1;
	i = 0;
	ans = (char *)malloc(sizeof(char) * (len_of_int(n) + 1));
	if (ans)
		return (0);
	if (n < 0)
		bool_ = 0;
	a = a_value_of_itoa(n);
	while (a >= 10)
	{
		ans[i++] = a % 10 + 48;
		a = a / 10;
	}
	ans[i++] = a % 10 + 48;
	if (bool_ == 0)
		ans[i++] = '-';
	ans[i] = '\0';
	ft_strrev(ans);
	return (ans);
}
