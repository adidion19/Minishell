/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_redi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:37:17 by adidion           #+#    #+#             */
/*   Updated: 2021/11/28 16:38:09 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

int	ft_verify_redi(t_lst_cmd cmd, char **env)
{
	int	fd_infile;
	int	fd_outfile;
	int	r;

	fd_infile = -1;
	fd_outfile = -1;
	if (cmd.inf)
		fd_infile = ft_open_inf(cmd);
	if (cmd.outf)
		fd_outfile = ft_open_outf(cmd, cmd.append);
	r = ft_choose_command(cmd, &env);
	if (fd_infile != -1)
		ft_close_inf(fd_infile);
	if (fd_outfile != -1)
		ft_close_mode(fd_outfile);
	return (r);
}
