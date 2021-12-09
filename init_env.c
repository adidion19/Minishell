/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:17:12 by ybrutout          #+#    #+#             */
/*   Updated: 2021/12/09 10:43:39 by artmende         ###   ########.fr       */
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

char	**env_replace(char **new_env, char *type, char *replace)
{
	size_t	len_type;
	int		i;

	if (!new_env || !type || !replace)
		return (0);
	len_type = ft_strlen(type);
	i = 0;
	while (ft_strncmp(new_env[i], type, len_type) != 0)
		i++;
	free(new_env[i]);
	new_env[i] = ft_strjoin(type, replace);
	if (!new_env[i])
		exit(EXIT_FAILURE);
	return (new_env);
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
	size_t	len;
	char	*new;

	i = 0;
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

// a=5
// len is 1
// str[len] = '='
// str[len + 1] = '5'

char	*env_find_no_malloc_no_equal(char *search, char **src)
{
	int		i;
	char	*ret;
	int		len;

	i = 0;
	len = ft_strlen(search);
	ret = NULL;
	if (!len)
		return (NULL);
	while (src[i])
	{
		if (len && ft_strncmp(search, src[i], len) == 0 && src[i][len] == '=')
		{
			ret = &src[i][len + 1];
			break ;
		}
		i++;
	}
	return (ret);
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
//	if (len < 0)
//		return (NULL);
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		exit(EXIT_FAILURE);
	new_env[len] = NULL;
	while (env[++i])
	{
		len = ft_strlen(env[i]);
//		if (len < 0)
//			return (free_env(new_env, i + 1));
		new_env[i] = malloc(sizeof(char) * (len + 1));
		if (!new_env[i])
			exit(EXIT_FAILURE);
		new_env[i] = ft_strncpy(env[i], new_env[i], len);
		if (!new_env[i])
			exit(EXIT_FAILURE);
	}
	return (new_env);
}
