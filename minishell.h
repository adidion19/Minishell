/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:15:21 by adidion           #+#    #+#             */
/*   Updated: 2021/11/09 14:47:32 by ybrutout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_cd(char *path, char **pwd, char **oldpwd);

/*
**	UTILS (COMPLET)
*/
size_t	len_lst(char **lst);
size_t	ft_strlen(char *str);
char	*ft_strncpy(char *src, char *dst, int nb);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcpy_after(char *src, char *after);

/*
**	UTILS_B
*/
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *src);

/*
**	ERROR
*/
char	**free_env(char **env, int nb);

/*
**	INIT_ENV
*/
int		env_replace(char **new_env, char *type, char *replace);
char	*env_find_the(char *search, char **src);
char	**init_env(char **env);

/*
**-------------------------------------COMMAND---------------------------------
*/

/* PWD */
int		ft_pwd(char **env);

/* ENV */
int		ft_env(char **env);

#endif
