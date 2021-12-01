/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:53:08 by artmende          #+#    #+#             */
/*   Updated: 2021/12/01 15:45:06 by artmende         ###   ########.fr       */
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
update_quote_state.c
 */
int				update_quote_state(char *str, t_quote_state *state);


/* 
add_input_output_to_cmd_node.c
 */
t_words_list	*add_output_no_append(t_lst_cmd *cmd_node, t_words_list *node,
	t_words_list **words_lst);
t_words_list	*add_output_append(t_lst_cmd *cmd_node, t_words_list *node,
	t_words_list **words_lst);
t_words_list	*add_input(t_lst_cmd *cmd_node, t_words_list *node,
	t_words_list **words_lst);
t_words_list	*add_heredoc(t_lst_cmd *cmd_node, t_words_list *node,
	t_words_list **words_lst);

/* 
display_error.c
 */
int	display_syntax_error(char c);
int	display_ambiguous_redirect(t_lst_cmd *cmd_node, char *var_name);

/* 
dollar_variables_handling.c
 */
char	*get_var_content(char *var_name, t_quote_state quote);
char	*get_var_name(char *str);
char	*expand_variables_in_single_word(char *word);
void	expand_variables_in_words_list(t_words_list *list);

/*
	get_end_of_word.c
*/
char			*get_end_of_word(char *str);

/*
	get_input_output.c
*/
t_words_list	*get_input_output(t_lst_cmd *cmd_node, t_words_list *words_lst);
void	open_outfile(t_lst_cmd *cmd_node);
void	open_infile(t_lst_cmd *cmd_node);
char	*resolve_redir_name(t_lst_cmd *cmd_node, char *word);

/*
	parser_utils.c
*/
int	have_redirection_symbol_not_alone(char	*str);
int	have_unquoted_space(char *str);
char	*remove_quotes_from_word(char *word, int i);
void	clean_cmd_node(t_lst_cmd *node);

/*
	parser.c
*/
void	handle_cmd_args_in_list(t_lst_cmd *node, t_words_list *words_list);
t_lst_cmd	*add_pipe_section(t_lst_cmd *list, char *str);
//t_lst_cmd	*parser(char *line);
//t_lst_cmd	*free_lst_cmd(t_lst_cmd *list);



/*
	verify_pipe_conditions.c
*/
int				verify_pipe_conditions(char *line);
int				have_only_spaces(char *from, char *to);

/*
	verify_redirections.c
*/
int	have_something_before_pipe(char *str);
int				verify_redirections(char *line);
int	redir_var_conditions(int i, char *word, char *var_name, char *var_content);
int	verify_redir_var(t_lst_cmd *cmd_node, char *word);

/*
	words_list.c
*/
t_words_list	*create_word_node(char	*word);
t_words_list	*insert_splitted_word(char **from, char *to, t_words_list *node);
t_words_list	*split_words_with_redirection_symbols(t_words_list *list);
t_words_list	*create_words_list(char *str);
t_words_list	*addback_word_to_list(t_words_list *lst, char *word);
t_words_list	*delete_node_words_list(t_words_list *list, t_words_list *node);
int				ft_lstsize_words(t_words_list *lst);
int				free_words_list(t_words_list *list, int flag);
t_words_list	*split_words_with_spaces_in_words_list(t_words_list *list);
void	insert_nodes_split_word(t_words_list *list, char *word, char *sep,
	int include_sep);

/*	PARSING_DEBUG_FUNCTIONS	*/
void			display_words_list(t_words_list	*list);
void			display_cmd_list(t_lst_cmd *lst);

#endif
