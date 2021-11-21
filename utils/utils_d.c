/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 13:33:20 by artmende          #+#    #+#             */
/*   Updated: 2021/11/21 17:41:57 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	duplicate_part_of_str : "from" and "to" are supposed to be part of the same
**	string and in order ("to" being after "from").
**
**	If "from" and "to" are the same, that single char will be copied anyway.
**
**	The pointer returned is always freeable.
*/

char	*duplicate_part_of_str(char *from, char *to)
{
	int		i;
	char	*ret;

	if (to < from)
		return (NULL);
	ret = ft_calloc(sizeof(char) * ((to - from) + 2));
	if (!ret)
		exit(EXIT_FAILURE);
	i = 0;
	while (from <= to)
	{
		ret[i] = *from;
		i++;
		from++;
	}
	return (ret);
}

void	free_array_of_string(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = 0;
		i++;
	}
	free(array);
}

t_lst_cmd	*free_lst_cmd(t_lst_cmd *list)
{
	t_lst_cmd	*temp;

	while (list)
	{
		free_array_of_string(list->arg);
		free(list->command);
		free(list->inf);
		free(list->outf);
		temp = list->next;
		free(list);
		list = temp;
	}
	return (NULL);
}
