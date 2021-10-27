/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:20:35 by ybrutout          #+#    #+#             */
/*   Updated: 2021/10/27 16:23:09 by ybrutout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char	*line;
	int		i;

	while (1)
	{
		line = readline("prompt :");
		if (line)
			printf("%s\n", line);
		if (line && *line)
		{
   			i = add_history (line);
			printf("%d\n", i);
		}
		free(line);
	}
	return (0);
}
