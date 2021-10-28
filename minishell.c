/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:20:35 by ybrutout          #+#    #+#             */
/*   Updated: 2021/10/28 13:56:25 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	int		i;

	while (1)
	{
		line = readline("\033[1m\033[36m prompt \x1b[0m");
//		line = readline("prompt ");
		//if (line)
		//	printf(BLUE);
		//	printf("%s", line);
		//	printf(RESET);
		if (line && *line)
		{
			i = add_history(line);
			//printf("%d\n", i);
		}
		free(line);
	}
	return (0);
}
