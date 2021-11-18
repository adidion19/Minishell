/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:51:17 by artmende          #+#    #+#             */
/*   Updated: 2021/11/18 19:05:35 by artmende         ###   ########.fr       */
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

int		is_char_in_str(char c, char *str)
{
	while (str && *str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}


void	free_tab_char(char **tab, int nb)
{
	int	i;

	i = -1;
	if (nb < 0)
		nb = (len_lst(tab)) + 1;
	if (nb > 0)
	{
		while (nb > 1)
		{
			free(tab[++i]);
			nb--;
		}
		free(tab);
	}
}
