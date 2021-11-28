/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:28:57 by adidion           #+#    #+#             */
/*   Updated: 2021/11/26 16:27:09 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmp(char *s1, char *s2)
{
	while (*s1 && s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (!*s1)
		return (0);
	return (*s1 - *s2);
}

char	**ft_sort_string_tab(char **tab)
{
	int		i;
	int		j;
	char	*k;

	j = 0;
	while (!j)
	{
		i = 0;
		j = 1;
		if (!tab[i])
			return (tab);
		while (tab[++i])
		{
			if (ft_cmp(tab[i - 1], tab[i]) > 0)
			{
				k = tab[i - 1];
				tab[i - 1] = tab[i];
				tab[i] = k;
				j = 0;
			}
		}
	}
	return (tab);
}

char	*ft_malloc_tmp(char *env)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(env) + 3));
	if (!tmp)
		exit(EXIT_FAILURE);
	return (tmp);
}

void	ft_print_export(char *env)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	tmp = ft_malloc_tmp(env);
	while (env[++i] && env[i] != '=')
		tmp[++j] = env[i];
	if (env[i])
		tmp[++j] = '=';
	if (env[i])
		tmp[++j] = '"';
	else
	{
		free(tmp);
		printf("declare -x %s\n", env);
		return ;
	}
	while (env[++i])
		tmp[++j] = env[i];
	tmp[++j] = '"';
	tmp[++j] = '\0';
	printf("declare -x %s\n", tmp);
	free(tmp);
}

int	export_no_arg(char **env)
{
	int	i;

	i = -1;
	env = ft_sort_string_tab(env);
	while (env[++i])
		ft_print_export(env[i]);
	return (0);
}
