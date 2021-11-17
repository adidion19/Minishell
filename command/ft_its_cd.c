/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_its_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:13:26 by adidion           #+#    #+#             */
/*   Updated: 2021/11/17 11:22:27 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_send_to_cd(t_lst_cmd cmd, char ***env, int bool)
{
	char	*pwd;
	char	*old_pwd;
	int		r;

	pwd = env_find_the("PWD=", *env);
	old_pwd = env_find_the("OLDPWD=", *env);
	if (bool == 1)
		r = ft_cd(cmd.arg[1], &pwd, &old_pwd);
	else
		r = ft_cd(NULL, &pwd, &old_pwd);
	*env = env_replace(*env, "PWD=", pwd);
	*env = env_replace(*env, "OLDPWD=", old_pwd);
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
					printf("minishell: cd: %s: No handeled", cmd.arg[1]);
					printf("options\n");
					return (1);
				}
			}
			else
				return (ft_send_to_cd(cmd, env, 0));
		}
	}
	return (257);
}
