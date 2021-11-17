/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_its_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:57:26 by adidion           #+#    #+#             */
/*   Updated: 2021/11/17 12:53:27 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_its_pwd(t_lst_cmd cmd, int r, char **env)
{
	if (r != 257)
		return (r);
	if (ft_strlen(cmd.command) == 3)
	{
		if (ft_strncmp(cmd.command, "pwd", 3) == 0)
		{
			return (ft_pwd(env));
		}
	}
	return (257);
}
