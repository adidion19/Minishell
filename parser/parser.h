/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:53:08 by artmende          #+#    #+#             */
/*   Updated: 2021/11/19 15:45:25 by artmende         ###   ########.fr       */
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

void			update_quote_state(char *str, t_quote_state *state);
int				ft_lstsize_words(t_words_list *lst);
t_words_list	*add_word_to_list(t_words_list *lst, char *word);
void			copy_args_from_word_list(char **array, t_words_list *list);
void			free_word_list(t_words_list *list, int flag);

void			extract_cmd_array(t_lst_cmd *node, char *str);
char			*get_end_of_word(char *str);

t_words_list	*create_words_list(char *str);

#endif
