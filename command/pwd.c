/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:00:02 by adidion           #+#    #+#             */
/*   Updated: 2021/11/09 16:08:33 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	va chercher et imprime la valeur du pwd actuel.
*/

int	ft_pwd(char **env)
{
	int		i;
	char	*pwd;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp("PWD=", env[i], 4) == 0)
		{
			pwd = ft_strcpy_after(env[i], "PWD=");
			if (!pwd)
				return (1);
			printf("%s\n", pwd);
			free(pwd);
			break ;
		}
	}
	return (0);
}
