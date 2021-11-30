/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:05:02 by artmende          #+#    #+#             */
/*   Updated: 2021/11/28 19:02:02 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_starts_with_space(char *str)
{
	if (!str || !ft_isspace(str[0]))
		return (0);
	return (1);
}

int	str_ends_with_space(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	if (i == 0 || !ft_isspace(str[i - 1]))
		return (0);
	return (1);
}

int	str_have_more_than_one_word(char *str)
{
	if (!str)
		return (0);
	while (*str && ft_isspace(*str))
		str++;
	while (*str && !ft_isspace(*str))
		str++;
	while (*str && ft_isspace(*str))
		str++;
	if (*str && !ft_isspace(*str))
		return (1);
	return (0);
}

/*
	add_ptr_to_ptrarray :
	This function adds a pointer to an existing array of pointer.
	If the original array doesn't exist (ptrarray == 0), ptr will be added to a
	newly created array.

	ptrarray needs to be either null of freeable.
*/

void	**add_ptr_to_ptrarray(void **ptrarray, void *ptr)
{
	int		array_len;
	int		i;
	void	**new_array;

	array_len = 0;
	while (ptrarray && ptrarray[array_len])
		array_len++;
	new_array = ft_calloc(sizeof(void *) * (array_len + 2));
	i = 0;
	while (i < array_len)
	{
		new_array[i] = ptrarray[i];
		i++;
	}
	new_array[i] = ptr;
	free(ptrarray);
	return (new_array);
}

int	is_ptr_in_ptrarray(void **ptrarray, void *ptr)
{
	int	i;

	i = 0;
	while (ptrarray && ptrarray[i])
	{
		if (ptr == ptrarray[i])
			return (1);
		i++;
	}
	return (0);
}
