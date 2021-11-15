/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:15:21 by adidion           #+#    #+#             */
/*   Updated: 2021/11/15 16:36:55 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_lst_cmd
{
	char				*command;
	char				**arg; //arg[0] = nom de la commande
	char				*inf;
	char				*outf;
	int					infd;
	int					outfd;
	struct s_lst_cmd	*next;
}	t_lst_cmd;

typedef struct s_minishell
{
	t_lst_cmd	*start;
	char		**env;
}	t_minishell;

/*
**	FT_ATOI
*/

int				ft_isspace(char c);
long			ft_return_of_strtol(int neg);
long			ft_strtol(const char *str);
int				ft_atoi(const char *str);

/*
**	FT_ITOA
*/

char			*ft_strrev(char *str);
int				len_of_int(int n);
unsigned int	a_value_of_itoa(int n);
char			*ft_itoa(int n);

/*
**	UTILS (COMPLET)
*/
size_t			len_lst(char **lst);
size_t			ft_strlen(char *str);
char			*ft_strncpy(char *src, char *dst, int nb);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strcpy_after(char *src, char *after);

/*
**	UTILS_B
*/
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(const char *src);
char			*ft_strjoin_2(char *s1, char *s2, int k);

/*
**	UTILS_C
*/
void			*ft_calloc(size_t nmemb);
void			*ft_memset(void *ptr, int c, size_t size);

/*
**	FT_SPLIT
*/

char			**ft_split(char const *s, char c);

/*
**	ERROR
*/
char			**free_env(char **env, int nb);

/*
**	INIT_ENV
*/
int				env_replace(char **new_env, char *type, char *replace);
char			*env_find_the(char *search, char **src);
char			**init_env(char **env);

/*
** -------------------------------------COMMAND---------------------------------
*/

/* PWD */
int				ft_pwd(char **env);

/* ENV */
int				ft_env(t_lst_cmd *cmd, char **env);

/* CD */

int				ft_cd(char *path, char **pwd, char **oldpwd);

/* EXIT */

int				ft_exit(char **arg);

/* ECHO */

int				ft_echo(char **arg, char **env, int bool);

/*
** ------------------------------------REDIRECTION-----------------------------
*/

/* FT_OPEN */

int				ft_open_mode(t_lst_cmd cmd, int bool);
int				ft_close_mode(int fd);
void			ft_putstr_fd(char *s, int fd);

#endif
