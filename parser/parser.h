/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:53:08 by artmende          #+#    #+#             */
/*   Updated: 2021/11/24 14:58:59 by artmende         ###   ########.fr       */
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

int				update_quote_state(char *str, t_quote_state *state);


void			copy_args_from_word_list(char **array, t_words_list *list);


void			extract_cmd_array(t_lst_cmd *node, char *str);




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

/*
	words_list.c
*/
t_words_list	*split_words_with_redirection_symbols(t_words_list *list);
t_words_list	*create_words_list(char *str);
t_words_list	*add_word_to_list(t_words_list *lst, char *word);
t_words_list	*delete_node_words_list(t_words_list *list, t_words_list *node);
int				ft_lstsize_words(t_words_list *lst);
void			free_words_list(t_words_list *list, int flag);

int	have_redirection_symbol_not_alone(char	*str);

/*
	get_end_of_word.c
*/
char			*get_end_of_word(char *str);

/*
	get_input_output.c
*/
t_words_list	*get_input_output(t_lst_cmd *cmd_node, t_words_list *words_lst);




void	display_words_list(t_words_list	*list);
int	display_syntax_error(char c);
#endif
