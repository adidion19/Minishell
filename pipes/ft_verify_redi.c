/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_redi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:37:17 by adidion           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/30 11:39:17 by adidion          ###   ########.fr       */
=======
/*   Updated: 2021/11/28 16:38:09 by artmende         ###   ########.fr       */
>>>>>>> 8fbd262ff74ea9183417b795f6a1e311cb07cc26
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

int	ft_verify_redi(t_lst_cmd cmd, char **env)
{
	int	fd_infile;
	int	fd_outfile;
	int	r;

	fd_infile = 0;
	fd_outfile = 0;
	if (cmd.inf)
		fd_infile = ft_open_inf(cmd);
	//	dup2(0 ,0);
	if (cmd.outf)
<<<<<<< HEAD
		fd_outfile = ft_open_mode(cmd, cmd.append);
	if (fd_infile == -1 || fd_outfile == -1)
		return (1);
=======
		fd_outfile = ft_open_outf(cmd, cmd.append);
>>>>>>> 8fbd262ff74ea9183417b795f6a1e311cb07cc26
	r = ft_choose_command(cmd, &env);
	if (cmd.inf && fd_infile != -1)
		ft_close_inf(fd_infile);
	if (cmd.outf && fd_outfile != -1)
		ft_close_mode(fd_outfile);
	return (r);
}
