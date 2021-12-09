/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:53:57 by ybrutout          #+#    #+#             */
/*   Updated: 2021/12/09 13:14:02 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freee(int k, char *s1, char *s2)
{
	if (k == 3 || k == 1)
		free(s1);
	if (k == 3 || k == 2)
		free(s2);
}

char	*ft_strjoin_2(char *s1, char *s2, int k)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	*str;

	i = -1;
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		exit(EXIT_FAILURE);
	while (s1[++i])
		str[i] = s1[i];
	j = i;
	i = -1;
	while (s2[++i])
		str[j++] = s2[i];
	str[j] = '\0';
	ft_freee(k, s1, s2);
	return (str);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		exit(EXIT_FAILURE);
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_s;
	size_t	len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	new_s = malloc(sizeof(char) * (len + 1));
	if (!new_s)
		exit(EXIT_FAILURE);
	i = -1;
	j = -1;
	while (s1[++i])
		new_s[i] = s1[i];
	while (s2[++j])
		new_s[i++] = s2[j];
	new_s[i] = '\0';
	return (new_s);
}
