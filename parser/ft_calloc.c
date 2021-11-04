/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:12:35 by artmende          #+#    #+#             */
/*   Updated: 2021/11/04 18:15:19 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

void	*ft_calloc(size_t nmemb)
{
	void	*ret;

	ret = malloc(sizeof(nmemb));
	if (!ret)
		return (NULL);
	else
		return(ft_memset(ret, 0, nmemb));
}
