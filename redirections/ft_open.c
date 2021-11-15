/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:09:26 by adidion           #+#    #+#             */
/*   Updated: 2021/11/15 15:24:19 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	if (s && fd)
	{
		while (s[++i])
			write(fd, &s[i], 1);
	}
}

/*
**	si bool == 1 : redirection >
**	si bool == 0 : redirection >>
** /!\ TRES IMPORTANT : apres avoir appele open_mode
	, il faut appeler close mode !!
**	return : le fd si open ressuit, sinon -1 -> return a verif en appel
*/

int	ft_open_mode(t_lst_cmd cmd, int bool)
{
	int	fd;

	if (bool == 1)
		fd = open(cmd.outf, O_RDWR | O_TRUNC | O_CREAT, 00777);
	if (bool == 0)
		fd = open(cmd.outf, O_RDWR | O_APPEND | O_CREAT, 00777);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nFile doesn't exist, or you don't have the ", 0);
		ft_putstr_fd("right accesses to it\n", 0);
		return (-1);
	}
	dup2(fd, 1);
	return (fd);
}

int	ft_close_mode(int fd)
{
	dup2(1, fd);
	if (close(fd) == -1)
		return (-1);
	return (0);
}
