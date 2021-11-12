/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:38:11 by ybrutout          #+#    #+#             */
/*   Updated: 2021/11/12 17:36:53 by ybrutout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_env_strncpy(char *src, char *dst, int len)
{
	int	i;
	int	j;

	if (!src || !dst)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len && src[j])
	{
		if (src[j] == "'" || src[j] == '"')
		{
			j++;
			continue;
		}
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

size_t	env_strlen(char *str)
{
	size_t	count;
	int		i;

	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == "'")
			continue;
		count++;
	}
	return (count);
}

/*
fonction strlen_env terminer mainteannt la mettre a la place des autres strlen
vérifier que chaque endoirt j'ai besoin de changer " ou '
a faire :
	-	gestion de la mémoire quand on change d'env
	-	il ne peut pas avoir de caractere speciaux dans le nom de la valeur
	-	faire la gestion des différentes erreures.
*/

int	check_the_value(char *str, char **env)
{
	int 	i;
	int		j;
	int		equal;
	char	*tmp;

	i = -1;
	equal = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			equal = 1;
			break;
		}
		if (str[i] == ' ')
			return (-1);
	}
	if (str[i] == '=' && (i == 0 || str[i - 1] == ' '))
		return (-1);
	if (equal == -1)
		return (0);
	tmp = malloc(sizeof(char) * (i + 2));
	tmp[i + 1] = '\0';
	tmp = ft_strncpy(str, tmp, i + 2);
	j = -1;
	while (env[++j])
	{
		if (!ft_strncmp(tmp, env[j], i + 1))
		{
			free(tmp);
			return (i + 1);
		}
	}
	free(tmp);
	return (1);
}

int	env_change(char *str, char ***env, int len_value)
{
	char 	*nw_str;
	char	*old_str;
	char	**tmp;
	size_t	len;
	int		i;

	len = ft_strlen(str);
	nw_str = malloc(sizeof(char) * (len + 1));
	if (!nw_str)
		return (1);
	tmp = *env;
	nw_str = ft_strncpy(str, nw_str, len);
	i = -1;
	while(tmp[++i])
	{
		if (!ft_strncmp(tmp[i], nw_str, len_value))
		{
			old_str = (*env)[i];
			(*env)[i] = nw_str;
			free(old_str);
			break ;
		}
	}
	return (0);
}

int	env_add(char *str, char ***env)
{
	size_t	lenenv;
	char	**new_env;
	char	**tmp;
	int		i;

	lenenv = len_lst(*env);
	tmp = *env;
	new_env = malloc(sizeof(char *) * (lenenv + 1));
	if (!new_env)
		return (1);
	new_env[lenenv] = NULL;
	i = -1;
	while (tmp[++i])
	{
		new_env[i] = malloc(sizeof(char) * (ft_strlen(tmp[i]) + 1));
		if (!new_env[i])
			return (1);
		ft_strncpy(tmp[i], new_env[i], ft_strlen(tmp[i]));
	}
	new_env[i] = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_env[i])
		return (1);
	ft_strncpy(str, new_env[i], ft_strlen(str));
	*env = new_env;
	return (0);
}

int	ft_export(t_lst_cmd *cmd, char ***env)
{
	int		i;
	int		ret;
	int		status;
	char	**old_env;
	int		j;//test

	i = 0;
	if (!cmd->arg[1])
	{
		ft_env(cmd, *env);
		return (0);
	}
	status = 0;
	while (cmd->arg[++i])
	{
		ret = check_the_value(cmd->arg[i], *env);
		if (ret <= 0)
		{
			if (ret < 0)
				status = 1;
			continue;
		}
		old_env = *env;
		if (ret > 1)
		{
			if (env_change(cmd->arg[i], env, ret))
				return (1);
		}
		if (ret == 1)
		{
			if (env_add(cmd->arg[i], env))
			{
				return (1);
			}
		}
		j = -1;
	}
	return (status);
}

/*faire en sort que ca boucle pour rajouter les valeurs a ajouter a l'environnement */

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
		cmd->arg = malloc(sizeof (char *) * 3); //si je mets 5 arguments (donc malloc de 6) ca segfault
		cmd->arg[0] = "export";
		cmd->arg[1] = "A=''";
		cmd->arg[2] = NULL;
		cmd->arg[3] = NULL;
		cmd->arg[4] = NULL;
		cmd->command = "export";
		cmd->inf = NULL;
		cmd->infd = 0;
		cmd->outf = NULL;
		cmd->outfd = 0;
		cmd->next = NULL;
		nw_env = init_env(env);
		ret = ft_export(cmd, &nw_env);
		i = -1;
		while (nw_env[++i])
			printf("%s\n", nw_env[i]);
		printf("ret == %d\n", ret);
	}
	return (0);
}

/*
//printf("str == '%s'\n", tmp);
while ((*env)[++j])
			printf("%s\n", (*env)[j]);
		exit(EXIT_FAILURE);
*/
