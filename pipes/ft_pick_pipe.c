/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pick_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:56:51 by adidion           #+#    #+#             */
/*   Updated: 2021/11/18 10:24:47 by adidion          ###   ########.fr       */
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

int	ft_pick_pipe(t_lst_cmd *cmd, char **env)
{
	if (ft_lstsize(cmd) == 1)
		return (ft_verify_redi(*cmd, env));
	if (ft_lstsize(cmd) == 2)
		return (ft_one_pipe(cmd, env));
}
