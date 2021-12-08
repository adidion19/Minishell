/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:45:26 by adidion           #+#    #+#             */
/*   Updated: 2021/12/08 15:03:29 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	in_string(char c, char c2)
{
	if (c == c2)
		return (1);
	return (0);
}

static int	count_word(char *str, char charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (in_string(str[i], charset))
			i++;
		if (!(in_string(str[i], charset)) && str[i] != 0)
		{
			while (!(in_string(str[i], charset)) && str[i])
				i++;
			count++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		index;
	char	**tab;

	i = 0;
	j = 0;
	index = 0;
	if (!s)
		return (0);
	tab = malloc(sizeof(*tab) * (count_word((char *)s, c) + 2));
	if (!tab)
		exit(EXIT_FAILURE);
	while (index < count_word((char *)s, c))
	{
		tab[index] = malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
		if (!(tab))
			exit(EXIT_FAILURE);
		while (s[i] && in_string(((char *)s)[i], c))
			i++;
		while (s[i] && !in_string(((char *)s)[i], c))
			tab[index][j++] = s[i++];
		tab[index++][j] = '\0';
		j = 0;
	}
	tab[index] = 0;
	return (tab);
}
