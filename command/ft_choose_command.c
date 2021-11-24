/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choose_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:58:00 by adidion           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/24 17:54:57 by adidion          ###   ########.fr       */
=======
/*   Updated: 2021/11/23 17:01:05 by ybrutout         ###   ########.fr       */
>>>>>>> df4f42798f8fb5044cbd07fc17a2d09656a6cf30
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
	r = ft_its_echo(cmd, r);
	r = ft_its_env(cmd, r, *env);
	r = ft_its_exit(cmd, r);
	r = ft_its_export(cmd, r, env);
	r = ft_its_pwd(cmd, r);
	r = ft_its_unset(cmd, r, env);
	if (r == 257)
		return (ft_other_command(cmd, *env));
	return (r);
}


int	main(int ac, char **av, char **envv)
{
	t_lst_cmd	cmd;

<<<<<<< HEAD
	cmd.command = av[2];
	cmd.arg = av + 2;
	cmd.inf = av[1];
=======
	if (ac < 0)
		write(1, "probleme\n", 9);
	cmd.command = av[1];
	cmd.arg = av + 1;
	cmd.inf = NULL;
>>>>>>> df4f42798f8fb5044cbd07fc17a2d09656a6cf30
	envv = init_env(envv);
	printf("%d\n", ft_heredoc(cmd, envv));
}
<<<<<<< HEAD
=======
*/
>>>>>>> df4f42798f8fb5044cbd07fc17a2d09656a6cf30
