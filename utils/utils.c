/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:30:35 by ybrutout          #+#    #+#             */
/*   Updated: 2021/11/19 11:50:24 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	len_lst(char **lst)
{
	size_t	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst[i])
		i++;
	return (i);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strncpy(char *src, char *dst, int nb)
{
	int	i;

	if (!src || !dst)
		return (NULL);
	i = -1;
	while (++i < nb)
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcpy_after(char *src, char *after)
{
	size_t	len_af;
	size_t	len_src;
	size_t	i;
	char	*dst;

	if (!src || !after)
		return (NULL);
	len_af = ft_strlen(after);
	len_src = ft_strlen(src) - len_af;
	i = -1;
	dst = malloc(sizeof (char) * (len_src + 1));
	if (!dst)
		return (NULL);
	while (++i < len_src)
		dst[i] = src[len_af + i];
	dst[i] = '\0';
	return (dst);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1 || !s2 || n > ft_strlen((char *)s1))
		return (-1);
	while (s1[i] == s2[i] && i < n - 1 && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
