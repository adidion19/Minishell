/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:20:35 by ybrutout          #+#    #+#             */
/*   Updated: 2021/11/19 17:45:16 by adidion          ###   ########.fr       */
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
	if (result < 0)
		result = -1;
	result++;
	if (result >= 1000)
	{
		printf("minishell:");
		printf(" warning: shell level (%d) too high, resetting to 1\n", result);
		result = 1;
	}
	free(env[i]);
	env[i] = ft_strjoin("SHLVL=", ft_itoa(result));
	return (env);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	int		i;

	env = init_env(env);
	ft_minishell_lvl(env, ac, av);
	while (1)
	{
		line = readline("$> ");
		if (line && *line)
		{
			i = add_history(line);
		}
		free(line);
	}
	return (0);
}
