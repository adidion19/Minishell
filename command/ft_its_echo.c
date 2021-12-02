/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_its_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:58:24 by adidion           #+#    #+#             */
/*   Updated: 2021/12/02 11:02:43 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_its_echo(t_lst_cmd cmd, int r)
{
	if (r != 257)
		return (r);
	if (ft_strlen(cmd.command) == 4)
	{
		if (ft_strncmp_maj(cmd.command, "echo", 4) == 0)
		{
			if (cmd.heredoc)
				heredoc_2(cmd);
			return (ft_echo(cmd.arg + 1, 0));
		}
	}
	return (257);
}
