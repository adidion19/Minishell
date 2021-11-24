/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_redi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:37:17 by adidion           #+#    #+#             */
/*   Updated: 2021/11/24 17:55:20 by adidion          ###   ########.fr       */
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
		fd_outfile = ft_open_mode(cmd, cmd.append);
	r = ft_choose_command(cmd, &env);
	if (fd_infile != -1)
		ft_close_inf(fd_infile);
	if (fd_outfile != -1)
		ft_close_mode(fd_outfile);
	return (r);
}
