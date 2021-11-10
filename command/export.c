/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:38:11 by ybrutout          #+#    #+#             */
/*   Updated: 2021/11/10 15:47:52 by ybrutout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**new_env(char *str, char **env)
{
	size_t	len;
	int		i;
	char	**cpy;

	len = len_lst(env);
	cpy = malloc(sizeof(char *) * (len + 2));
	if (!cpy)
		return (NULL);
	cpy[len + 1] = NULL;
	i = -1;
	while (env[++i])
	{
		len = ft_strlen(env[i]);
		cpy[i] = malloc(sizeof(char) * (len + 1));
		if (!cpy[i])
			return (free_env(cpy, i + 1));
		cpy[i] = ft_strncpy(env[i], cpy[i], len);
	}
	len = ft_strlen(str);
	cpy[i] = malloc(sizeof(char) * (len + 1));
	if (!cpy[i])
		return (free_env(cpy, i + 1));
	cpy[i] = ft_strncpy(str, cpy[i], len);
	return (cpy);
}

char	*find_the_equal(char **arg)
{
	int	i;
	int	j;

	i = -1;
	while (arg[++i])
	{
		j = 0;
		while (arg[i][j] && arg[i][j] != '=')
			j++;
		if (arg[i][j] == '=')
			break ;
	}
	if (!arg[i])
		return (NULL);
	return (arg[i]);
}

int	ft_export(t_lst_cmd *cmd, char ***env)
{
	char	*val;
	char	**tmp_env;

	if (!cmd->arg[1])
		return (ft_env(cmd, *env));
	val = find_the_equal(cmd->arg);
	if (!val)
		return (0);
	tmp_env = *env;
	*env = new_env(val, *env);
	if (!env)
	{
		*env = tmp_env;
		return (-1);
	}
	free_env(tmp_env, (len_lst(*env) + 1));
	return (0);
}

/*
int	main(int argc, char **argv, char **env)
{
	t_lst_cmd	*cmd;
	char		**nw_env;
	int			ret;
	int			i;

	if (argc > 0)
	{
		printf("%s\n\n",argv[0]);
		cmd = malloc(sizeof(t_lst_cmd) * 1);
		cmd->arg = malloc(sizeof (char *) * 3);
		cmd->arg[0] = "export";
		cmd->arg[1] = "coucou=va";
		cmd->arg[2] = NULL;
		cmd->command = "export";
		cmd->inf = NULL;
		cmd->infd = 0;
		cmd->outf = NULL;
		cmd->outfd = 0;
		cmd->next = NULL;
		nw_env = init_env(env);
		ret = ft_export(cmd, &nw_env);
		cmd->arg[1] = NULL;
		i = 0;
		ft_env(cmd, nw_env);
	}
	return (0);
}
*/
