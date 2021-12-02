/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_its_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:27:02 by adidion           #+#    #+#             */
/*   Updated: 2021/12/02 11:03:26 by adidion          ###   ########.fr       */
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
				if (cmd.heredoc)
					heredoc_2(cmd);
				return (ft_env(cmd, env));
			}
			else
			{
				if (cmd.heredoc)
					heredoc_2(cmd);
				write(2, "minishell: env: No arguments handeled for env\n", 47);
				return (127);
			}
		}
	}
	return (257);
}
