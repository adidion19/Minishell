/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:51:17 by artmende          #+#    #+#             */
/*   Updated: 2021/12/01 16:58:26 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t nmemb)
{
	void	*ret;

	ret = malloc(nmemb);
	if (!ret)
		exit(EXIT_FAILURE);
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

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c_e;
	char	*s_e;

	c_e = (char)c;
	s_e = (char *)s;
	i = 0;
	while (s[i])
	{
		if (s[i] == c_e)
			return (&s_e[i]);
		i++;
	}
	if (c == 0)
		return (&s_e[i]);
	return (0);
}

void	free_tab_char(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
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
