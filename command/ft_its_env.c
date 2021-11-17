/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_its_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:27:02 by adidion           #+#    #+#             */
/*   Updated: 2021/11/17 10:51:30 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_its_env(t_lst_cmd cmd, int r, char **env)
{
	if (r != 257)
		return (r);
	if (ft_strlen(cmd.command) == 3)
	{
		if (ft_strncmp(cmd.command, "env", 3) == 0)
		{
			if (!cmd.arg[1])
				return (ft_env(cmd, env));
			else
			{
				printf("minishell: env: Too much arguments for this command");
				return (127);
			}
		}
	}
	return (257);
}