/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_its_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:13:26 by adidion           #+#    #+#             */
/*   Updated: 2021/12/08 17:10:04 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_send_to_cd(t_lst_cmd cmd, char ***env, int bool)
{
	char	*pwd;
	char	*old_pwd;
	int		r;
	char	*tst;

	if (cmd.heredoc)
		heredoc_2(cmd);
	if (!(tst = env_find_the("PWD", *env)))
		nw_env(env, "PWD=");
	free(tst);
	if (!(tst = env_find_the("OLDPWD", *env)))
		nw_env(env, "OLDPWD=");
	free(tst);
	pwd = env_find_the("PWD=", *env);
	old_pwd = env_find_the("OLDPWD=", *env);
	if (bool == 1)
		r = ft_cd(cmd.arg[1], &pwd, &old_pwd, *env);
	else
		r = ft_cd(NULL, &pwd, &old_pwd, *env);
	*env = env_replace(*env, "PWD=", pwd);
	free(pwd);
	*env = env_replace(*env, "OLDPWD=", old_pwd);
	free(old_pwd);
	return (r);
}

int	ft_count_arg(char **arg)
{
	int	i;

	i = -1;
	if (!arg)
		return (0);
	while (arg[++i])
		;
	return (i);
}

int	ft_its_cd(t_lst_cmd cmd, char ***env)
{
	if (ft_strlen(cmd.command) == 2)
	{
		if (ft_strncmp(cmd.command, "cd", 2) == 0)
		{
			if (ft_count_arg(cmd.arg) > 1)
			{
				if (cmd.arg[1][0] != '-')
					return (ft_send_to_cd(cmd, env, 1));
				else
				{
					if (cmd.heredoc)
						heredoc_2(cmd);
					write(2, "exotic_shell: cd: ", 18);
					write(2, cmd.arg[1], ft_strlen(cmd.arg[1]));
					write(2, ": No handeled options\n", 23);
					return (1);
				}
			}
			else
				return (ft_send_to_cd(cmd, env, 0));
		}
	}
	return (257);
}
