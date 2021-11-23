/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_its_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:04:11 by adidion           #+#    #+#             */
/*   Updated: 2021/11/23 13:43:32 by ybrutout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_its_unset(t_lst_cmd cmd, int r, char ***env)
{
	if (r != 257)
		return (r);
	if (ft_strlen(cmd.command) == 5)
	{
		if (ft_strncmp(cmd.command, "unset", 5) == 0)
			return (ft_unset(cmd, env));
	}
	return (257);
}
