/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:48:13 by adidion           #+#    #+#             */
/*   Updated: 2021/11/09 13:16:59 by ybrutout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
besoin d'envoyer le le char **env du main
*/

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
