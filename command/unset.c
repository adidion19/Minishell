/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:55:48 by yannahbruto       #+#    #+#             */
/*   Updated: 2021/11/23 15:30:19 by ybrutout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_arg(char *str, char **env)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	len = ft_strlen(str);
	while (env[++i])
	{
		j = -1;
		while (++j < len)
		{
			if (env[i][j] != str[j])
				break ;
		}
		if (j == len && env[i][j] == '=')
			break ;
	}
	if (!env[i])
		return (0);
	else
		return (1 + i);
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

int	ft_unset(t_lst_cmd cmd, char ***env)
{
	int		ret;
	int		i;
	char	**oldenv;

	if (!cmd.arg[1])
		return (1);
	i = 0;
	while (cmd.arg[++i])
	{
		ret = check_arg(cmd.arg[i], *env);
		if (!ret)
			continue ;
		oldenv = *env;
		*env = remove_variable(ret - 1, env);
		if (!*env)
			return (1);
		free_tab_char(oldenv, -1);
	}
	return (0);
}
