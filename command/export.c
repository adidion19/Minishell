/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:38:11 by ybrutout          #+#    #+#             */
/*   Updated: 2021/11/19 13:49:16 by adidion          ###   ########.fr       */
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

int	env_check_arg(char *arg, char **env)
{
	int	i;
	int	j;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == ' ')
			return (-1);
		if (arg[i] == '=')
			break ;
	}
	if (arg[i] != '=')
		return (0);
	if (i == 0)
		return (-1);
	j = -1;
	while (env[++j])
	{
		if (!ft_strncmp(arg, env[j], i + 1))
			return (i + 1);
	}
	return (1);
}

int	nw_env(char ***env, char *str)
{
	int		len;
	int		lenstr;
	char	**nw_env;

	len = len_lst(*env);
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
	char	**oldenv;

	i = 0;
	status = 0;
	if (!cmd.arg[1])
		return (ft_env(cmd, *env));
	while (cmd.arg[++i])
	{
		ret = env_check_arg(cmd.arg[i], *env);
		if (ret < 1)
		{
			if (ret < 0)
				status = 1;
			continue ;
		}
		oldenv = *env;
		if (ret == 1)
		{
			if (nw_env(env, cmd.arg[i]))
				return (1);
			free_tab_char(oldenv, -1);
		}
		else
			if (env_change(env, cmd.arg[i], ret))
				return (1);
	}
	return (status);
}
/*
char *initstr(char *str)
{
	char	*tmp;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	tmp = malloc(sizeof(char) * (len + 1));
	tmp[len] = '\0';
	i = -1;
	while (++i < len)
		tmp[i] = str[i];
	return (tmp);
}
/*
int	main(int argc, char **argv, char **env)
{
	char 		**envcpy;
	t_lst_cmd	*cmd;
	if (argc == 2)
		printf("argv == %s\n", argv[0]);
	envcpy = init_env(env);
	cmd = malloc(sizeof(t_lst_cmd));
	cmd->command = NULL;
	cmd->inf = NULL;
	cmd->outf = NULL;
	cmd->outfd = 0;
	cmd->infd = 0;
	cmd->arg = malloc(sizeof(char *) * 10);
	cmd->arg[0] = "export";
	cmd->arg[1] = "A+=c";
	cmd->arg[2] = "coucou=12";
	cmd->arg[3] = NULL;
	cmd->arg[4] = NULL;
	cmd->arg[5] = NULL;
	cmd->arg[6] = NULL;
	cmd->arg[7] = NULL;
	cmd->arg[8] = NULL;
	cmd->arg[9] = NULL;
	int ret = 0;

	ret = ft_export(cmd, &envcpy);
	cmd->arg[1] = NULL;
	write(1, "\n\n--------------------------\n", 29);
	ft_env(*cmd, envcpy);
	write(1, "\n", 1);
	printf("ret == %d\n", ret);
	system("leaks a.out");
	return (0);
}
*/