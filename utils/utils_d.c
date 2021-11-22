/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 13:33:20 by artmende          #+#    #+#             */
/*   Updated: 2021/11/22 14:21:41 by artmende         ###   ########.fr       */
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

char	*ft_strnstr(char *str, char *to_find, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (to_find[0] == 0)
		return (str);
	while (str[i] && i < len)
	{
		if (str[i] == to_find[0])
		{
			while (str[i + j] == to_find[j] && i + j < len)
			{
				if (to_find[j + 1] == 0)
					return (&str[i]);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (0);
}
