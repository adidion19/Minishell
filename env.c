/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:48:13 by adidion           #+#    #+#             */
/*   Updated: 2021/10/28 16:15:39 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n - 1 && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_env(char **env)
{
	int		i;
	char	*pwd;
	char	*oldpwd;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp("PWD", env[i], 3) == 0)
		{
			pwd = getenv("PWD");
			if (!pwd)
				return (1);
			printf("PWD=%s\n", pwd);
		}
		else if (ft_strncmp("OLDPWD", env[i], 6) == 0)
		{
			oldpwd = getenv("OLDPWD");
			if (!oldpwd)
				return (1);
			printf("OLDPWD=%s\n", getenv("OLDPWD"));
		}
		else
			printf("%s\n", env[i]);
	}
	return (0);
}
