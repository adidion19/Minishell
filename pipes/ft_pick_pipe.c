/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pick_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:56:51 by adidion           #+#    #+#             */
/*   Updated: 2021/11/30 17:05:00 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_lstsize(t_lst_cmd *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	ft_look_cmd(t_lst_cmd cmd, char **env)
{
	if (!strncmp(cmd.command, "cd", 2) || !ft_strncmp(cmd.command, "exit", 4)
		|| !ft_strncmp(cmd.command, "unset", 5)
		|| !ft_strncmp(cmd.command, "export", 6))
		return (ft_choose_command(cmd, env));
	else
		return (ft_verify_redi(cmd, env));
}

int	ft_pick_pipe(t_lst_cmd *cmd, char **env)
{
	if (!cmd)
		return (127);
	if (ft_lstsize(cmd) == 1)
		return (ft_look_cmd(*cmd, env));
	if (ft_lstsize(cmd) == 2)
		return (ft_one_pipe(cmd, env));
	//else
	//	return (ft_multiple_pipe(cmd, env, ft_lstsize(cmd)));
	return (1);
}
