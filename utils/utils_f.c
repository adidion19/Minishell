/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:05:02 by artmende          #+#    #+#             */
/*   Updated: 2021/11/27 18:06:14 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_starts_with_space(char *str)
{
	if (!str || !ft_isspace(str[0]))
		return (0);
	return (1);
}

int	str_ends_with_space(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	if (i == 0 || !ft_isspace(str[i - 1]))
		return (0);
	return (1);
}

int	str_have_more_than_one_word(char *str)
{
	if (!str)
		return (0);
	while (*str && ft_isspace(*str))
		str++;
	while (*str && !ft_isspace(*str))
		str++;
	while (*str && ft_isspace(*str))
		str++;
	if (*str && !ft_isspace(*str))
		return (1);
	return (0);
}
