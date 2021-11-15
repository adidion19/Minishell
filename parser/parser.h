/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:53:08 by artmende          #+#    #+#             */
/*   Updated: 2021/11/15 16:56:40 by artmende         ###   ########.fr       */
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

void			update_quote_state(char c, t_quote_state *state);
int				ft_lstsize_words(t_words_list *lst);
t_words_list	*add_word_to_list(t_words_list *lst, char *from, char *to);
void			copy_args_from_word_list(char **array, t_words_list *list);
void			free_word_list(t_words_list *list, int flag);

#endif
