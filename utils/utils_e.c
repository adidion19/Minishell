/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:31:03 by artmende          #+#    #+#             */
/*   Updated: 2021/12/09 11:28:49 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 && !s2)
		return (0);
	if ((!s1 && s2) || (s1 && !s2))
		return (1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != 0)
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*end_of_word;

	if (!s1 || !set)
		return (NULL);
	end_of_word = (char *)s1 + ft_strlen((char *)s1);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	while (end_of_word > s1 && ft_strchr(set, *end_of_word))
		end_of_word--;
	return (duplicate_part_of_str((char *)s1, end_of_word));
}

// this ft_strtrim is not working correctly
/* 
static int	is_in_base(char str, const char *base)
{
	int	i;

	i = 0;
	while (base[i] != 0)
	{
		if (str == base[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*malzero(void)
{
	char	*s0;

	s0 = malloc(sizeof(char));
	if (!s0)
		exit(EXIT_FAILURE);
	s0[0] = 0;
	return (s0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*res;

	if (!s1 || !set)
		return (0);
	i = 0;
	j = ft_strlen((char *)s1) - 1;
	k = 0;
	while (is_in_base(s1[i], set))
		i++;
	while (is_in_base(s1[j], set))
		j--;
	if (j - i <= 0)
		return (malzero());
	res = malloc(sizeof(char) * (2 + (j - i)));
	if (!res)
		exit(EXIT_FAILURE);
	while (i++ <= j)
		res[k++] = s1[i - 1];
	res[k] = 0;
	return (res);
}

 */

/*
	remove_chars_from_str :

	It makes an allocated copy of str without including the chars whose
	addresses are in ptrarray.

	ptrarray is a null terminated array of pointers. The array can be NULL, in
	that case, the original string will simply be duplicated.

	The returned string is freeable. However, the original string doesn't need
	to be.
*/

char	*remove_chars_from_str(char *str, void **ptrarray)
{
	char	*ret;
	int		len;
	int		i;

	len = ft_strlen(str);
	if (!str)
		return (NULL);
	ret = ft_calloc(sizeof(char) * (1 + len));
	if (!ret)
		exit(EXIT_FAILURE);
	i = 0;
	while (*str)
	{
		if (is_ptr_in_ptrarray(ptrarray, str))
		{
			str++;
			continue ;
		}
		ret[i] = *str;
		str++;
		i++;
	}
	return (ret);
}
