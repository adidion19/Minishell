/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_redi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:37:17 by adidion           #+#    #+#             */
/*   Updated: 2021/11/30 17:17:14 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

int	ft_verify_redi(t_lst_cmd cmd, char **env)
{
	int	fd_infile;
	int	fd_outfile;
	int pid;
	int status;

	fd_infile = 0;
	fd_outfile = 0;
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
	if (cmd.inf)
		fd_infile = ft_open_inf(cmd);
	if (cmd.outf)
		fd_outfile = ft_open_outf(cmd, cmd.append);
	if (fd_infile == -1 || fd_outfile == -1)
		exit (1);
	g_global.status = ft_choose_command(cmd, env);
	if (cmd.inf && fd_infile != -1)
		ft_close_inf(fd_infile);
	if (cmd.outf && fd_outfile != -1)
		ft_close_mode(fd_outfile);
		exit(0);
	}
	waitpid(pid, &status, 0);
	return (status);
}
