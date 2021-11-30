/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:29:13 by artmende          #+#    #+#             */
/*   Updated: 2021/11/30 16:01:44 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../parser.h"


int	main(int argc, char **argv, char **envp)
{



	printf("\nline to parse : '%s'\n\n", argv[1]);


	if (argc < 2)
		return (0);

	t_lst_cmd	*cmd_list;
	cmd_list = parser(argv[1]);
	display_cmd_list(cmd_list);
	printf("\nFreeing command list...\n");
	free_lst_cmd(cmd_list);
	printf("done !\n");

	system("leaks a.out");






	
	return (0);
}