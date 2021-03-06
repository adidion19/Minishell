/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pick_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:56:51 by adidion           #+#    #+#             */
/*   Updated: 2021/12/10 15:18:43 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_look_cmd(t_lst_cmd cmd, char ***env)
{
	if (!cmd.command && cmd.heredoc)
		return (g_global.status = heredoc_2(cmd));
	if (!cmd.command)
		return (ft_verify_redi(cmd, env));
	if (!strncmp(cmd.command, "cd", 2) || !ft_strncmp(cmd.command, "exit", 4)
		|| !ft_strncmp(cmd.command, "unset", 5)
		|| !ft_strncmp(cmd.command, "export", 6))
		return (g_global.status = ft_choose_command(cmd, env));
	else
		return (ft_verify_redi(cmd, env));
}

int	ft_pick_pipe(t_lst_cmd *cmd, char ***env)
{
	set_signal_outside(cmd);
	g_global.start = 0;
	if (cmd && ft_lstsize(cmd) == 1)
		ft_look_cmd(*cmd, env);
	else if (cmd)
		ft_multiple_pipe(cmd, env);
	set_signal_default();
	return (1);
}
