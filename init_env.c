/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:17:12 by ybrutout          #+#    #+#             */
/*   Updated: 2021/11/09 14:11:09 by ybrutout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	env_replace remplace la valeur de 'type' par 'replace'
**	dans le tableau d'environnement.
**	/!\ Bien mettre le '=' aussi non il ne sera pas remis
**	dans la nouvelle string.
**	return '1' si tout a fonctionné aussi non ça retourne '0'
*/

int		env_replace(char **new_env, char *type, char *replace)
{
	size_t	len_type;
	size_t	len_replace;
	int		i;

	if (!new_env || !type || !replace)
		return (0);
	len_type = ft_strlen(type);
	len_replace = ft_strlen(replace);
	i = 0;
	while (ft_strncmp(new_env[i], type, len_type) != 0)
		i++;
	free(new_env[i]);
	new_env[i] = ft_strjoin(type, replace);
	if (!new_env[i])
		return (0);
	return (1);
}

/*
**	env_find_the retourne la string correspondant à la
**	recherche en enlevant la recherche.
**	/!\ Bien mettre le '=' aussi non il n'est pas enlever
**	de la string renvoyé.
*/

char	*env_find_the(char *search, char **src)
{
	int		i;
	int		j;
	size_t	len;
	char	*new;

	i = 0;
	j = 0;
	len = ft_strlen(search);
	new = NULL;
	while (src[i])
	{
		if (ft_strncmp(search, src[i], len) == 0)
		{
			new = ft_strcpy_after(src[i], search);
			break ;
		}
		i++;
	}
	return (new);
}

/*
**	Initialisation de l'environnement. La fonction reprend
**	la liste d'environnement reçu en argument pour la recopier
**	dans un nouveau tableau de string.
**	return le nouveau tableau d'environnement.
*/

char	**init_env(char **env)
{
	char	**new_env;
	size_t	len;
	int		i;

	len = len_lst(env);
	i = -1;
	if (len < 0)
		return (NULL);
	new_env = malloc(sizeof(char *) * len + 1);
	if (!new_env)
		return (NULL);
	new_env[len] = NULL;
	while (env[++i])
	{
		len = ft_strlen(env[i]);
		if (len < 0)
			return (free_env(new_env, i + 1));
		new_env[i] = malloc(sizeof(char) * (len + 1));
		if (!new_env)
			return (free_env(new_env, i + 1));
		new_env[i] = ft_strncpy(env[i], new_env[i], len);
		if (!new_env[i])
			return (free_env(new_env, i + 2));
	}
	return (new_env);
}

/*
int		main(int argc, char **argv, char **env)
{
	char	**new_env;
	char	*pwd;
	int		i;
	int		len;
	int		ret;

	if (argc == 1)
	{
		printf("argv == %s\n", argv[0]);
		new_env = init_env(env);
		i = -1;
		while (new_env[++i])
			printf("%s\n", new_env[i]);
		pwd = env_find_the("LANG=", new_env);
		printf("pwd == %s\n", pwd);
		ret = env_replace(new_env, "PWD=", "coucou");
		i = -1;
		while (new_env[++i])
			printf("%s\n", new_env[i]);
		printf("ret == %d\n", ret);
		len = len_lst(new_env);
		free_env(new_env, len + 1);
	}
	return (0);
}*/
