/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:38:11 by ybrutout          #+#    #+#             */
/*   Updated: 2021/11/10 16:15:33 by ybrutout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	how_much_equal(char **arg)
{
	int count;
	int	i;
	int	j;

	i = -1;
	count = 0;
	while (arg[++i])
	{
		j = -1;
		while(arg[i][++j] && arg[i][j] != '=')
		{
			if (arg[i][j] == '=')
			{
				count++;
				break ;
			}
		}
	}
	return (count);
}

int	ft_export(t_lst_cmd *cmd, char ***env)
{
	char	*val;
	char	**tmp_env;
	int		count;
	int		i;
	int		j;

	count = how_much_equal(cmd->arg);
	i = -1;
	while
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
		cmd->arg = malloc(sizeof (char *) * 3);
		cmd->arg[0] = "export";
		cmd->arg[1] = "A=a";
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

