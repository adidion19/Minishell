/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:09:26 by adidion           #+#    #+#             */
/*   Updated: 2021/12/09 11:33:06 by adidion          ###   ########.fr       */
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
**	a envoyer ici si la redirection est <
**	/!\ TRES IMPORTANT : apres avoir appele open_inf
	, il faut appeler close_inf!!
**	return : le fd si open reussit, sinon -1 -> return a verif en appel
**	! a tester quand on aura le parsing fait pour cette partie
*/

int	ft_open_inf(t_lst_cmd cmd)
{
	int	fd;
	int	error;

	errno = 0;
	fd = open(cmd.inf, O_RDONLY);
	error = errno;
	if (fd == -1)
	{
		write(2, "exotic_shell: ", 14);
		write(2, cmd.outf, ft_strlen(cmd.outf));
		write (2, ": ", 2);
		write(2, strerror(error), ft_strlen(strerror(error)));
		return (-1);
	}
	dup2(fd, 0);
	return (fd);
}

int	ft_close_inf(int fd)
{
	if (close(fd) == -1)
		return (-1);
	return (0);
}

/*
**	si bool == 0 : redirection >
**	si bool == 1 : redirection >>
** /!\ TRES IMPORTANT : apres avoir appele open_mode
	, il faut appeler close mode !!
**	return : le fd si open reussit, sinon -1 -> return a verif en appel
*/

int	ft_open_outf(t_lst_cmd cmd, int bool)
{
	int	fd;
	int	error;

	errno = 0;
	if (bool == 0)
		fd = open(cmd.outf, O_WRONLY | O_TRUNC);
	if (bool == 1)
		fd = open(cmd.outf, O_WRONLY | O_APPEND);
	error = errno;
	if (fd == -1)
	{
		write(2, "exotic_shell: ", 14);
		write(2, cmd.outf, ft_strlen(cmd.outf));
		write (2, ": ", 2);
		write(2, strerror(error), ft_strlen(strerror(error)));
		return (-1);
	}
	dup2(fd, 1);
	return (fd);
}

int	ft_close_mode(int fd)
{
	if (close(fd) == -1)
		return (-1);
	return (0);
}
