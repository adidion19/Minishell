/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:20:35 by ybrutout          #+#    #+#             */
/*   Updated: 2021/10/29 16:46:48 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
faudra degager cette fonction, c'etait pour des tests
*/

char	**ft_minishell_lvl(char **env, int ac, char **av)
{
	int		i;
	int		result;

	i = -1;
	if (ac != 1 || av)
		;
	while (env[++i])
	{
		if (ft_strncmp("SHLVL=", env[i], 6) == 0)
			break ;
	}
	result = ft_atoi(env[i] + 6);
	result++;
	env[i] = ft_itoa(result);
	return (env);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	int		i;

	ft_minishell_lvl(env, ac, av);
	while (1)
	{
		line = readline("prompt $>");
		if (line && *line)
		{
			i = add_history(line);
		}
		free(line);
	}
	return (0);
}
