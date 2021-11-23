/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybrutout <ybrutout@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:15:21 by adidion           #+#    #+#             */
/*   Updated: 2021/11/23 15:26:51 by ybrutout         ###   ########.fr       */
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
# include <limits.h>
# include <termios.h>

typedef struct s_lst_cmd
{
	char				*command;
	char				**arg; //arg[0] = nom de la commande
	char				*inf;
	char				*outf;
	int					infd;
	int					outfd;
	int					bool; // 1 means append mode
	struct s_lst_cmd	*next;
}	t_lst_cmd;

typedef struct s_global
{
	t_lst_cmd	*start;
	int			status;
}	t_global;

t_global	g_global;

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
char			*ft_strchr(const char *s, int c);
void			free_tab_char(char **tab, int nb);
char			*malagain(char *from, char *add, int len_add);

/*
**	UTILS_D
*/
char			*duplicate_part_of_str(char *from, char *to);
void			free_array_of_string(char **array);
t_lst_cmd		*free_lst_cmd(t_lst_cmd *list); // returns a null pointer
char			*ft_strnstr(char *str, char *to_find, size_t len);
int				ft_strncmp_maj(const char *s1, const char *s2, size_t n);

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
char			**env_replace(char **new_env, char *type, char *replace);
char			*env_find_the(char *search, char **src);
char			**init_env(char **env);

/*
** -------------------------------------COMMAND---------------------------------
*/

/* PWD */
int				ft_pwd(char **env);

/* ENV */
int				ft_env(t_lst_cmd cmd, char **env);

/* CD */

int				ft_cd(char *path, char **pwd, char **oldpwd, char **env);

/* EXIT */

int				ft_exit(char **arg);

/* ECHO */

int				ft_echo(char **arg, int bool);

/* EXPORT */

int				ft_export(t_lst_cmd cmd, char ***env);

/* UNSET */

int				ft_unset(t_lst_cmd cmd, char ***env);

/* OTHER_COMMAND */

int				ft_other_command(t_lst_cmd cmd, char **env);

/* FT_ITS */

int				ft_choose_command(t_lst_cmd cmd, char ***env);
int				ft_its_cd(t_lst_cmd cmd, char ***env);
int				ft_its_echo(t_lst_cmd cmd, int r);
int				ft_its_env(t_lst_cmd cmd, int r, char **env);
int				ft_its_exit(t_lst_cmd cmd, int r);
int				ft_its_export(t_lst_cmd cmd, int r, char ***env);
int				ft_its_pwd(t_lst_cmd cmd, int r, char **env);
int				ft_its_unset(t_lst_cmd cmd, int r, char ***env);

/*
** ------------------------------------REDIRECTION-----------------------------
*/

/* FT_OPEN */

int				ft_open_mode(t_lst_cmd cmd, int bool);
int				ft_close_mode(int fd);
void			ft_putstr_fd(char *s, int fd);
int				ft_close_inf(int fd);
int				ft_open_inf(t_lst_cmd cmd);

/*
**--------------------------------------PIPE------------------------------------
*/

/* FT_VERIFY_REDI */

int				ft_verify_redi(t_lst_cmd cmd, char **env);

/*
**-------------------------------------SIGNAL-----------------------------------
*/

/*	SIGNAL	*/

void			set_signal(void);
void			ctrl_backslach(int signum);
void			ctrl_c(int signum);

void   			rl_replace_line(const char *text, int clear_undo);

#endif
