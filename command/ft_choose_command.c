/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choose_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:58:00 by adidion           #+#    #+#             */
/*   Updated: 2021/11/17 13:03:15 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	absolument tout a tester quand on aura le parsing, j'sens que ca va etre
	drole les segfault :')
**	return l'exit status de la commande
**	cmd : la structure de commandes du parsing
	env : un pointeur dereference sur l'environnement
*/
int	ft_choose_command(t_lst_cmd cmd, char ***env)
{
	int	r;

	if (!cmd.command)
		return (0);
	r = ft_its_cd(cmd, env);
	r = ft_its_echo(cmd, r, *env);
	r = ft_its_env(cmd, r, *env);
	r = ft_its_exit(cmd, r);
	r = ft_its_export(cmd, r, env);
	r = ft_its_pwd(cmd, r, *env);
	if (r != 257)
		return (ft_other_command(cmd, *env));
	return (r);
}
