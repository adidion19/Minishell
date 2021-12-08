/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_redi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:37:17 by adidion           #+#    #+#             */
/*   Updated: 2021/12/08 11:14:11 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

int	ft_verify_redi_2(t_lst_cmd cmd, char ***env)
{
	int	fd_infile;
	int	fd_outfile;

	fd_infile = 0;
	fd_outfile = 0;
	if (cmd.inf && cmd.heredoc == 0)
		fd_infile = ft_open_inf(cmd);
	// if (cmd.inf && cmd.heredoc)
		// ft_heredoc(cmd);
	if (cmd.outf)
		fd_outfile = ft_open_outf(cmd, cmd.append);
	if (fd_infile == -1 || fd_outfile == -1)
		exit (1);
	if (cmd.command)
		g_global.status = ft_choose_command(cmd, env);
	if (cmd.inf && fd_infile != -1 && cmd.heredoc == 0)
		ft_close_inf(fd_infile);
	if (cmd.outf && fd_outfile != -1)
		ft_close_mode(fd_outfile);
	return (g_global.status);
}

int	ft_verify_redi(t_lst_cmd cmd, char ***env)
{
	int	fd_infile;
	int	fd_outfile;
	int pid;
	int status;

	fd_infile = 0;
	fd_outfile = 0;
	signal(SIGQUIT, ctrl_backslash_status_to_131);
	signal(SIGINT, ctrl_c_status_to_130);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		signal(SIGQUIT, ctrl_backslash_inside);
		signal(SIGINT, ctrl_c_status_to_130);
		if (cmd.inf && cmd.heredoc == 0)
			fd_infile = ft_open_inf(cmd);
		if (cmd.inf && cmd.heredoc)
			ft_heredoc(cmd);
		if (cmd.outf)
			fd_outfile = ft_open_outf(cmd, cmd.append);
		if (fd_infile == -1 || fd_outfile == -1)
			exit (1);
		if (cmd.command)
			g_global.status = ft_choose_command(cmd, env);
		if (cmd.inf && fd_infile != -1 && cmd.heredoc == 0)
			ft_close_inf(fd_infile);
		if (cmd.outf && fd_outfile != -1)
			ft_close_mode(fd_outfile);
		exit(g_global.status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_global.status = WEXITSTATUS(status);
	set_signal();
	return (status);
}
