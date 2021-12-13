/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:31:03 by artmende          #+#    #+#             */
/*   Updated: 2021/12/13 11:02:15 by adidion          ###   ########.fr       */
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

void	neg(int i)
{
	if (i < 0)
		exit(EXIT_FAILURE);
}

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
