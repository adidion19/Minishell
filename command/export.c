/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:38:11 by ybrutout          #+#    #+#             */
/*   Updated: 2021/11/26 16:28:12 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cpy_env(char	**nw_env, char **env)
{
	int	i;
	int	len;

	i = -1;
	while (env[++i])
	{
		len = ft_strlen(env[i]);
		nw_env[i] = malloc(sizeof(char) * (len + 1));
		if (!nw_env)
			return (NULL);
		nw_env[i] = ft_strncpy(env[i], nw_env[i], ft_strlen(env[i]));
	}
	return (nw_env);
}

int	ft_error_export(char *arg)
{
	write(2, "minishell: export: '", 20);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	return (-1);
}

int	nw_env(char ***env, char *str)
{
	int		len;
	int		lenstr;
	char	**nw_env;
	char	**oldenv;

	len = len_lst(*env);
	oldenv = *env;
	nw_env = malloc(sizeof(char *) * (len + 2));
	nw_env[len + 1] = NULL;
	nw_env = cpy_env(nw_env, *env);
	if (!nw_env)
		return (-1);
	lenstr = ft_strlen(str);
	nw_env[len] = malloc(sizeof(char) * (lenstr + 1));
	if (!nw_env[len])
		return (-1);
	nw_env[len] = ft_strncpy(str, nw_env[len], len);
	*env = nw_env;
	free_tab_char(oldenv, -1);
	return (0);
}

int	env_change(char ***env, char *str, int ret)
{
	int		i;
	char	*tmp;

	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp((*env)[i], str, ret))
		{
			tmp = (*env)[i];
			(*env)[i] = malloc(sizeof(char) * (ft_strlen(str) + 1));
			if (!(*env)[i])
				return (1);
			(*env)[i] = ft_strncpy(str, (*env)[i], ft_strlen(str));
			free(tmp);
			break ;
		}
	}
	return (0);
}

int	ft_export(t_lst_cmd cmd, char ***env)
{
	int		i;
	int		ret;
	int		status;

	i = 0;
	status = 0;
	if (!cmd.arg[1])
		return (export_no_arg(*env));
	while (cmd.arg[++i])
	{
		ret = env_check_arg(cmd.arg[i], *env);
		if (ret < 0)
			status = 1;
		if (ret == 1)
		{
			if (nw_env(env, cmd.arg[i]))
				return (1);
		}
		else if (ret > 1)
			if (env_change(env, cmd.arg[i], ret))
				return (1);
	}
	return (status);
}
