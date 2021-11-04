/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:36:04 by artmende          #+#    #+#             */
/*   Updated: 2021/11/04 18:13:14 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

void	*ft_memset(void *ptr, int c, size_t size)
{
	while (ptr && size)
	{
		((char *)ptr)[size - 1] = c;
		size--;
	}
	return (ptr);
}
