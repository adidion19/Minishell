/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_check_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:27:43 by adidion           #+#    #+#             */
/*   Updated: 2021/11/26 16:33:03 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env_check_arg_condition(char c)
{
	if (!((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9') || c == '_'))
		return (0);
	return (1);
}

int	env_check_arg(char *arg, char **env)
{
	int	i;
	int	j;

	i = -1;
	if (!arg[0])
		return (ft_error_export(arg));
	if (!((arg[0] >= 'a' && arg[0] <= 'z') || (arg[0] >= 'A' && arg[0] <= 'Z')
			|| arg[0] == '_'))
		return (ft_error_export(arg));
	while (arg[++i])
	{
		if (arg[i] == '=')
			break ;
		if (!ft_env_check_arg_condition(arg[i]))
			return (ft_error_export(arg));
	}
	if (arg[i] != '=')
		return (0);
	if (i == 0)
		return (-1);
	j = -1;
	while (env[++j])
		if (!ft_strncmp(arg, env[j], i + 1))
			return (i + 1);
	return (1);
}
