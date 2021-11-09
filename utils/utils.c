/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:30:35 by ybrutout          #+#    #+#             */
/*   Updated: 2021/11/09 12:55:52 by ybrutout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	len_lst(char **lst)
{
	size_t	i;

	i = 0;
	if (!lst)
		return (-1);
	while (lst[i])
		i++;
	return (i);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strncpy(char *src, char *dst, int nb)
{
	int	i;

	if (!src || !dst)
		return (NULL);
	i = -1;
	while (++i < nb)
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}
