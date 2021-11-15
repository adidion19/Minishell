/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:51:17 by artmende          #+#    #+#             */
/*   Updated: 2021/11/15 11:52:59 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t nmemb)
{
	void	*ret;

	ret = malloc(sizeof(nmemb));
	if (!ret)
		return (NULL);
	else
		return(ft_memset(ret, 0, nmemb));
}

void	*ft_memset(void *ptr, int c, size_t size)
{
	while (ptr && size)
	{
		((char *)ptr)[size - 1] = c;
		size--;
	}
	return (ptr);
}
