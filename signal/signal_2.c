/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:27:29 by adidion           #+#    #+#             */
/*   Updated: 2021/12/09 11:27:45 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_backslash_inside(int sig)
{
	write(2, "Quit: 3\n", 8);
	rl_replace_line("", 0);
	rl_on_new_line();
	(void)sig;
}
