/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:51:17 by artmende          #+#    #+#             */
/*   Updated: 2021/11/21 14:54:07 by adidion          ###   ########.fr       */
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
		return (ft_memset(ret, 0, nmemb));
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

int	is_char_in_str(char c, char *str)
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

/*
**	The malagain function allocates enough memory for a copy of string "from"
**	and "len_add" bytes of string "add". It does the copy and returns a pointer
**	to it.
**	It also frees the memory pointed by "from".
**
**	In case "from" and "add" are both null pointers, or in case "from" is a
**	null pointer and "len_add" is zero, it still returns an allocated string
**	with length zero.
*/

char	*malagain(char *from, char *add, int len_add)
{
	int		i;
	int		len_from;
	char	*ret;

	len_from = ft_strlen(from);
	ret = ft_calloc(sizeof(char) * (len_from + len_add + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len_from)
	{
		ret[i] = from[i];
		i++;
	}
	while (len_add && add)
	{
		ret[i] = *add;
		add++;
		i++;
		len_add--;
	}
	free(from);
	return (ret);
}
