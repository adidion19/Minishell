/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:55:48 by yannahbruto       #+#    #+#             */
/*   Updated: 2021/12/08 17:10:27 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error_unset(char *arg)
{
	write(2, "exotic_shell: unset: '", 22);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	return (-1);
}

int	check_arg(char *str, char **env)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	len = ft_strlen(str);
	if (!str[0])
		return (ft_error_unset(str));
	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')
			|| str[0] == '_'))
		return (ft_error_unset(str));
	while (str[++i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
			return (ft_error_unset(str));
	}
	i = -1;
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
		exit(EXIT_FAILURE);
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
			exit(EXIT_FAILURE);
		ft_strncpy((*env)[j], tmp[i], lenstr);
		j++;
	}
	free_tab_char(*env, len);
	return (tmp);
}

int	ft_unset(t_lst_cmd cmd, char ***env)
{
	int		ret;
	int		i;

	if (!cmd.arg[1])
		return (0);
	i = 0;
	while (cmd.arg[++i])
	{
		ret = check_arg(cmd.arg[i], *env);
		if (!ret)
			continue ;
		if (ret == -1)
			return (1);
		*env = remove_variable(ret - 1, env);
		if (!*env)
			exit(EXIT_FAILURE);
	}
	return (0);
}
