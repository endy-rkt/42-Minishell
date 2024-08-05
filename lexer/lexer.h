/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:28:55 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/05 23:51:57 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include "../header.h"

typedef enum {
    TK_WORD,
    TK_PIPE,
	TK_REDIR,
    TK_REDIR_IN,
    TK_REDIR_OUT,
    TK_REDIR_OUT2,
    TK_HEREDOC,
	TK_OR,
	TK_AND
} token_type;

typedef struct s_token
{
	char			*value;
	token_type		type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

int		is_operator(char c);
t_token	*tk_create(char *value, token_type type, t_token *tk_prev);
t_token	*tk_last(t_token *tk);
void	tk_add_back(t_token **tk, t_token *tk_new);
void	tk_clear(t_token **tk);
void	tk_print(t_token *tk); //0
int		idx_of_last(char *str, char c);
int		idx_of_first(char *str, char c);

#endif