/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:53:08 by artmende          #+#    #+#             */
/*   Updated: 2021/12/13 10:54:25 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_words_list
{
	char				*word;
	struct s_words_list	*next;
}	t_words_list;

typedef struct s_quote_state
{
	int	simple_quote;
	int	double_quote;
	int	global_quote;
}	t_quote_state;

/*
	add_pipe_section.c
*/

t_lst_cmd		*add_pipe_section(t_lst_cmd *list, char *str, char **env);
void			handle_cmd_args_in_list(t_lst_cmd *node,
					t_words_list *words_list);

/*
	words_list_1.c
*/

t_words_list	*create_words_list(char *str);
t_words_list	*addback_word_to_list(t_words_list *lst, char *word);
t_words_list	*split_words_with_redirection_symbols(t_words_list *list);
t_words_list	*delete_node_words_list(t_words_list *list, t_words_list *node);
int				free_words_list(t_words_list *list, int flag);

/*
	words_list_2.c
*/

t_words_list	*split_words_with_spaces_in_words_list(t_words_list *list);
void			insert_nodes_split_word(t_words_list *list, char *word,
					char *sep, int include_sep);
t_words_list	*insert_splitted_word(char **from, char *to,
					t_words_list *node);
t_words_list	*create_word_node(char	*word);
int				ft_lstsize_words(t_words_list *lst);

/*
	get_input_output.c
*/

t_words_list	*get_input_output(t_lst_cmd *cmd_node, t_words_list *words_lst,
					char **env);
char			*resolve_redir_name(t_lst_cmd *cmd_node, char *word,
					char **env);
void			open_outfile(t_lst_cmd *cmd_node);
void			open_infile(t_lst_cmd *cmd_node);

/*
	add_input_output_to_cmd_node.c
*/

t_words_list	*add_output_no_append(t_lst_cmd *cmd_node, t_words_list *node,
					t_words_list **words_lst, char **env);
t_words_list	*add_output_append(t_lst_cmd *cmd_node, t_words_list *node,
					t_words_list **words_lst, char **env);
t_words_list	*add_input(t_lst_cmd *cmd_node, t_words_list *node,
					t_words_list **words_lst, char **env);
t_words_list	*add_heredoc(t_lst_cmd *cmd_node, t_words_list *node,
					t_words_list **words_lst);

/*
	dollar_variables_handling.c
*/

int				have_var_to_expand(char *word);
t_words_list	*expand_variables_in_words_list(t_words_list *list, char **env);
char			*expand_variables_in_single_word(char *word, char **env);
char			*get_var_name(char *str);
char			*get_var_content(char *var_name, t_quote_state quote,
					char **env);

/*
	dollar_variables_handling_2.c
*/

int				is_valid_var_char(char c);

/*
	verify_pipe_conditions.c
*/

int				verify_pipe_conditions(char *line);
int				have_only_spaces(char *from, char *to);

/*
	verify_redirections.c
*/

int				verify_redirections(char *line);
int				have_something_before_pipe(char *str);
int				verify_redir_var(t_lst_cmd *cmd_node, char *word, char **env);
int				redir_var_conditions(int i, char *word, char *var_name,
					char *var_content);

/*
	update_quote_state.c
*/

int				update_quote_state(char *str, t_quote_state *state);

/*
	display_error.c
*/

int				display_syntax_error(char c);
int				display_ambiguous_redirect(t_lst_cmd *cmd_node, char *var_name);

/*
	parser_utils.c
*/

int				have_redirection_symbol_not_alone(char	*str);
int				have_unquoted_space(char *str);
char			*remove_quotes_from_word(char *word, int i);
void			clean_cmd_node(t_lst_cmd *node);
char			*get_end_of_word(char *str);

/*
	parsing_debug_functions.c
*/

void			display_words_list(t_words_list	*list);
void			display_cmd_list(t_lst_cmd *lst);
t_lst_cmd		*reverse_lst_cmd(t_lst_cmd *list);

#endif
