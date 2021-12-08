/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_its_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:27:02 by adidion           #+#    #+#             */
/*   Updated: 2021/12/08 17:03:47 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_its_env(t_lst_cmd cmd, int r, char **env)
{
	if (r != 257)
		return (r);
	if (ft_strlen(cmd.command) == 3)
	{
		if (ft_strncmp_maj(cmd.command, "env", 3) == 0)
		{
			if (!cmd.arg[1])
			{
				return (ft_env(cmd, env));
			}
			else
			{
				write(2, "exotic_shell: env: No arguments handeled for env\n",
					49);
				return (127);
			}
		}
	}
	return (257);
}
