/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:15:21 by adidion           #+#    #+#             */
/*   Updated: 2021/12/01 17:08:23 by adidion          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>

typedef struct s_lst_cmd
{
	char				*command;
	char				**arg; //arg[0] = nom de la commande
	char				*inf;
	char				*outf;
	int					infd; // probably not needed
	int					outfd; // probably not needed
	int					append; // 1 means append mode
	int					heredoc; // 1 means that inf is not a file, but the keyword for heredoc
	int					delete_this_node;
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
char			*ft_strnstr(char *str, char *to_find, size_t len);
int				ft_strncmp_maj(const char *s1, const char *s2, size_t n);

/*
**	UTILS_E
*/
int				ft_strcmp(char *s1, char *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*remove_chars_from_str(char *str, void **ptrarray);

/*
**	UTILS_F
*/
int				str_starts_with_space(char *str);
int				str_ends_with_space(char *str);
int				str_have_more_than_one_word(char *str);
void			**add_ptr_to_ptrarray(void **ptrarray, void *ptr);
int				is_ptr_in_ptrarray(void **ptrarray, void *ptr);

/*
**	UTILS_G
*/
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);

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
int				ft_pwd(void);

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
int				export_no_arg(char **env);
int				env_check_arg(char *arg, char **env);
int				ft_error_export(char *arg);

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
int				ft_its_pwd(t_lst_cmd cmd, int r);
int				ft_its_unset(t_lst_cmd cmd, int r, char ***env);

/*
** ------------------------------------REDIRECTION-----------------------------
*/

/* FT_OPEN */

int				ft_open_outf(t_lst_cmd cmd, int bool);
int				ft_close_mode(int fd);
void			ft_putstr_fd(char *s, int fd);
int				ft_close_inf(int fd);
int				ft_open_inf(t_lst_cmd cmd);

/* FT_HEREDOC */

int				ft_heredoc(t_lst_cmd cmd, char **env);

/*
**--------------------------------------PIPE------------------------------------
*/

/* FT_VERIFY_REDI */

int				ft_verify_redi(t_lst_cmd cmd, char ***env);

/* FT_ONE_PIPE */

int				ft_one_pipe(t_lst_cmd *cmd, char ***env);

/* FT_MULTIPLE_PIPE */

int				ft_multiple_pipe(t_lst_cmd *cmd, char ***env, int size);

/* FT_PICK_PIPE */

int				ft_pick_pipe(t_lst_cmd *cmd, char ***env);

/*
**-------------------------------------SIGNAL-----------------------------------
*/

/*	SIGNAL	*/

void			set_signal(void);
void			ctrl_backslach(int signum);
void			ctrl_c(int signum);

void			rl_replace_line(const char *text, int clear_undo);

/*
**-------------------------------------PARSER-----------------------------------
*/

t_lst_cmd		*parser(char *line);
t_lst_cmd		*free_lst_cmd(t_lst_cmd *list); // returns a null pointer

#endif
