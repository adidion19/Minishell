/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:31:03 by artmende          #+#    #+#             */
/*   Updated: 2021/11/26 16:42:37 by artmende         ###   ########.fr       */
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
	if (s0)
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
	j = ft_strlen(s1) - 1;
	k = 0;
	while (is_in_base(s1[i], set))
		i++;
	while (is_in_base(s1[j], set))
		j--;
	if (j - i <= 0)
		return (malzero());
	res = malloc(sizeof(char) * (2 + (j - i)));
	if (res)
	{
		while (i++ <= j)
			res[k++] = s1[i - 1];
		res[k] = 0;
	}
	return (res);
}

/*
	remove_pair_of_char_from_str :

	It makes an allocated copy of str without including the two chars c1 and c2.

	c1 and c2 are pointers. They are the addresses of two char in the original
	string.
	c1 or c2 or both can be null pointer. In that case, it will simply duplicate
	the original string.

	The returned string is freeable. However, the original string doesn't need
	to be.
*/

char	*remove_pair_of_char_from_str(char *str, char *c1, char *c2)
{
	char	*ret;
	char	*str_sav;
	int		len;
	int		i;

	len = ft_strlen(str);
	if (!len)
		return (str);
	ret = ft_calloc(sizeof(char) * (1 + len));
	if (!ret)
		exit(EXIT_FAILURE);
	i = 0;
	str_sav = str;
	while (*str)
	{
		if (str == c1 || str == c2)
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
