/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:17:12 by ybrutout          #+#    #+#             */
/*   Updated: 2021/11/09 13:02:30 by ybrutout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	initiation de l'environnement. reprend la liste d'environnement reçu en argument pour
**	la recopier dans une nouveau tableau de string.
*/
char	**init_env(char **env)
{
	char	**new_env;
	size_t	len;
	int		i;

	len = len_lst(env);
	i = 0;
	if (len < 0)
		return (NULL);
	new_env = malloc(sizeof(char *) * len + 1);
	if (!new_env)
		return (NULL);
	new_env[len] = NULL;
	while (env[i])
	{
		len = ft_strlen(env[i]);
		if (len < 0)
			return (free_env(new_env, i + 1));
		new_env[i] = malloc(sizeof(char) * (len + 1));
		if (!new_env)
			return (free_env(new_env, i + 1));
		new_env[i] = ft_strncpy(env[i], new_env[i], len);
		if (!new_env[i])
			return(free_env(new_env, i + 2));
		i++;
	}
	return (new_env);
}

int		main(int argc, char **argv, char **env)
{
	char	**new_env;
	int		i;
	int		len;

	if (argc == 1)
	{
		printf("argv == %s\n", argv[0]);
		new_env = init_env(env);
		i = -1;
		while (new_env[++i])
		{
			printf("%s\n", new_env[i]);
		}
		len = len_lst(new_env);
		free_env(new_env, len + 1);
	}
	return (0);
}
