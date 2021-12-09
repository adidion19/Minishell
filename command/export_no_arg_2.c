/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:10:40 by adidion           #+#    #+#             */
/*   Updated: 2021/12/09 10:59:32 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}

int	ft_len_export(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		;
	return (i);
}

char	**ft_cpy_tab(char **env)
{
	int		i;
	char	**tmp;

	tmp = malloc(sizeof(char *) * (ft_len_export(env) + 1));
	if (!tmp)
		exit(EXIT_FAILURE);
	tmp[ft_len_export(env)] = NULL;
	i = -1;
	while (env[++i])
	{
		tmp[i] = malloc(sizeof(char) * ft_strlen(env[i]) + 1);
		if (!tmp[i])
			exit(EXIT_FAILURE);
		tmp[i] = ft_strcpy(tmp[i], env[i]);
	}
	return (tmp);
}