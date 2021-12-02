/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_its_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:00:58 by adidion           #+#    #+#             */
/*   Updated: 2021/12/02 11:03:37 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_its_exit(t_lst_cmd cmd, int r)
{
	if (r != 257)
		return (r);
	if (ft_strlen(cmd.command) == 4)
	{
		if (ft_strncmp(cmd.command, "exit", 4) == 0)
		{
			if (cmd.heredoc)
				heredoc_2(cmd);
			return (ft_exit(cmd.arg + 1));
		}
	}
	return (257);
}
