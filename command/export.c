/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:38:11 by ybrutout          #+#    #+#             */
/*   Updated: 2021/12/08 17:09:57 by artmende         ###   ########.fr       */
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
	write(2, "exotic_shell: export: '", 23);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	return (-1);
}

int	nw_env(char ***env, char *str)
{
	int		len;
	int		lenstr;
	char	**nw_env;
	//char	**oldenv;

	len = len_lst(*env);
	//oldenv = *env;
	nw_env = malloc(sizeof(char *) * (len + 2));
	if (!nw_env)
		exit(EXIT_FAILURE);
	nw_env[len + 1] = NULL;
	nw_env = cpy_env(nw_env, *env);
	if (!nw_env)
		exit(EXIT_FAILURE);
	lenstr = ft_strlen(str);
	nw_env[len] = malloc(sizeof(char) * (lenstr + 1));
	if (!nw_env[len])
		exit(EXIT_FAILURE);
	nw_env[len] = ft_strncpy(str, nw_env[len], lenstr);
	free_tab_char(*env, len_lst(*env));
	*env = nw_env;
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
				exit(EXIT_FAILURE);
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
