/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:15:21 by adidion           #+#    #+#             */
/*   Updated: 2021/12/10 19:08:59 by artmende         ###   ########.fr       */
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
# include <signal.h>

typedef struct s_lst_cmd
{
	char				*command;
	char				**arg;
	char				*inf;
	char				*outf;
	int					infd;
	int					outfd;
	int					append;
	int					heredoc;
	int					delete_this_node;
	struct s_lst_cmd	*next;
}	t_lst_cmd;

typedef struct s_global
{
	int			start;
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
int				ft_lstsize(t_lst_cmd *lst);

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
char			*env_find_no_malloc_no_equal(char *search, char **src);
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
int				nw_env(char ***env, char *str);
char			**ft_cpy_tab(char **env);
char			*ft_strcpy(char *dest, char *src);

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

int				ft_heredoc(t_lst_cmd cmd);
int				heredoc_2(t_lst_cmd cmd);

/*
**--------------------------------------PIPE------------------------------------
*/

/* FT_VERIFY_REDI */

int				ft_verify_redi(t_lst_cmd cmd, char ***env);
int				ft_verify_redi_2(t_lst_cmd cmd, char ***env);

/* FT_MULTIPLE_PIPE */

int				ft_multiple_pipe(t_lst_cmd *cmd, char ***env);

/* FT_PICK_PIPE */

int				ft_pick_pipe(t_lst_cmd *cmd, char ***env);

/*
**-------------------------------------SIGNAL-----------------------------------
*/

void			rl_replace_line(const char *text, int clear_undo);

/*	SET_SIGNAL_IN_OUT	*/

int				set_signal_outside(t_lst_cmd *cmd);
int				set_signal_inside(t_lst_cmd *cmd);

/*	SET_SIGNALS_DIFFERENT_SITUATIONS	*/

int				set_signal_default(void);
int				set_signal_outside_cmd_is_running_no_heredoc(void);
int				set_signal_outside_cmd_is_running_heredoc(void);
int				set_signal_inside_cmd_is_running_no_heredoc(void);
int				set_signal_inside_cmd_is_running_heredoc(void);

/*	SIGNAL_HANDLERS_DEFAULT	*/

void			sig_do_nothing(int sig);
void			ctrl_c_default(int signum);
void			ctrl_backslash_default(int sig);

/*	SIGNAL_HANDLERS_NO_HEREDOC	*/

void			ctrl_c_outside_no_heredoc(int sig);
void			ctrl_backslash_outside_no_heredoc(int sig);
void			ctrl_c_inside_no_heredoc(int sig);
void			ctrl_backslash_inside_no_heredoc(int sig);

/*	SIGNAL_HANDLERS_HEREDOC	*/

void	ctrl_c_outside_heredoc(int sig);
void	ctrl_backslash_outside_heredoc(int sig);
void	ctrl_c_inside_heredoc(int sig);
void	ctrl_backslash_inside_heredoc(int sig);

/*
**-------------------------------------PARSER-----------------------------------
*/

t_lst_cmd		*parser(char *line, char **env);
t_lst_cmd		*free_lst_cmd(t_lst_cmd *list); // returns a null pointer

#endif
