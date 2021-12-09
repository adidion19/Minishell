/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choose_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:58:00 by adidion           #+#    #+#             */
/*   Updated: 2021/12/09 10:47:00 by adidion          ###   ########.fr       */
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

int	heredoc_2(t_lst_cmd cmd)
{
	int		pid1;
	char	*line2;
	int		r;
	int		status;

	r = 0;
	status = 0;
	line2 = NULL;
	pid1 = fork();
	if (pid1 < 0)
		return (-1);
	if (pid1 == 0)
	{
		while (ft_strncmp(line2, cmd.inf, ft_strlen(cmd.inf))
			|| ft_strlen(line2) != ft_strlen(cmd.inf))
		{
			free(line2);
			line2 = readline("> ");
		}
		free(line2);
		exit(0);
	}
	waitpid(pid1, &status, 0);
	return (r);
}

int	ft_choose_command(t_lst_cmd cmd, char ***env)
{
	int	r;

	if (!cmd.command && cmd.heredoc)
		return (g_global.status = heredoc_2(cmd));
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

/*
int	main(int ac, char **av, char **envv)
{
	t_lst_cmd	cmd;
	char		*line;
	int r;
	int i;

	cmd.command = av[2];
	cmd.arg = av + 2;
	cmd.inf = av[1];
	cmd.outf = NULL;
	cmd.append = 0;
	line = NULL;
	envv = init_env(envv);
	//ft_verify_redi(cmd, envv);
	while (1)
	{
			//free(line);
		if (!ft_strcmp(line, "heredoc"))
		{
			r = ft_heredoc(cmd, envv);
		//	if (r < 0)
		//	{
		//		i = -1;
		//	while(++i < 9999999)
		//		;
		//	}
		// if (line)
		line = NULL;}
		else
		line = readline("$> ");
	}
}
*/