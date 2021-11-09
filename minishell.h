/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:15:21 by adidion           #+#    #+#             */
/*   Updated: 2021/11/09 12:59:37 by ybrutout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_pwd(int bool);
int		ft_env(char **env);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

/*
	UTILS
*/
size_t	len_lst(char **lst);
size_t	ft_strlen(char *str);
char	*ft_strncpy(char *src, char *dst, int nb);

/*
	ERROR
*/
char	**free_env(char **env, int nb);

#endif
