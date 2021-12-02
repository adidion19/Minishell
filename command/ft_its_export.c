/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_its_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:30:19 by adidion           #+#    #+#             */
/*   Updated: 2021/12/02 11:03:49 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_its_export(t_lst_cmd cmd, int r, char ***env)
{
	if (r != 257)
		return (r);
	if (ft_strlen(cmd.command) == 6)
	{
		if (ft_strncmp(cmd.command, "export", 6) == 0)
		{
			if (cmd.heredoc)
				heredoc_2(cmd);
			return (ft_export(cmd, env));
		}
	}
	return (257);
}
