/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_its_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:58:24 by adidion           #+#    #+#             */
/*   Updated: 2021/11/17 13:04:45 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_its_echo(t_lst_cmd cmd, int r, char **env)
{
	if (r != 257)
		return (r);
	if (ft_strlen(cmd.command) == 4)
	{
		if (ft_strncmp(cmd.command, "echo", 4) == 0)
		{
			(void)env;
			;// chopper la fontion de yannah pour
			//supprimer un char * dans un char **		
		}
	}
	return (257);
}
