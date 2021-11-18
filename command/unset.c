/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannahbrutout <yannahbrutout@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:55:48 by yannahbruto       #+#    #+#             */
/*   Updated: 2021/11/18 16:06:50 by yannahbruto      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_arg(char *str, char **env)
{
	int	i;
	int	j;
	int len;

	i = -1;
	len = ft_strlen(str);
	while (env[++i])
	{
		j = -1;
		while (++j < len)
		{
			if (env[i][j] != str[j])
				break;
		}
		if (j == len && env[i][j] == '=')
			break;
	}
	if (!env[i])
		return (0);
	else return (1 + i);
}

char	**remove_variable(int ret, char ***env)
{
	char	**tmp;
	int		len;
	int		lenstr;
	int		i;
	int		j;

	len = len_lst(*env);
	tmp = malloc(sizeof(char *) * len);
	if (!tmp)
		return (NULL);
	tmp[len - 1] = NULL;
	i = -1;
	j = 0;
	while (++i < (len - 1))
	{
		if (i == ret)
			j++;
		lenstr = ft_strlen((*env)[j]);
		tmp[i] = malloc(sizeof(char) * (lenstr + 1));
		if (!tmp[i])
			return (NULL);
		ft_strncpy((*env)[j], tmp[i], lenstr);
		j++;
	}
	return (tmp);
}

int	ft_unset(t_lst_cmd *cmd, char ***env)
{
	int		ret;
	int		i;
	char	**oldenv;

	if (!cmd->arg[1])
		return (0);
	i = 0;
	while (cmd->arg[++i])
	{
		ret = check_arg(cmd->arg[i], *env);
		if (!ret)
			continue ;
		oldenv = *env;
		*env = remove_variable(ret - 1, env);
		if (!*env)
			return (1);
		free_tab_char(oldenv, -1);
	}
	//write(1, "hey\n", 4);
	//cmd->arg[1] = NULL;
	//ft_env(*cmd, *env);
	return (0);
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
	cmd->arg[0] = "unset";
	cmd->arg[1] = "A";
	cmd->arg[2] = "coucou";
	cmd->arg[3] = NULL;
	cmd->arg[4] = NULL;
	cmd->arg[5] = NULL;
	cmd->arg[6] = NULL;
	cmd->arg[7] = NULL;
	cmd->arg[8] = NULL;
	cmd->arg[9] = NULL;
	int ret = 0;

	ret = ft_unset(cmd, &envcpy);
	cmd->arg[1] = NULL;
	write(1, "\n\n--------------------------\n", 29);
	ft_env(*cmd, envcpy);
	write(1, "\n", 1);
	printf("ret == %d\n", ret);
	return (0);
}*/