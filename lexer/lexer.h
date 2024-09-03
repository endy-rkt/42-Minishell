/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:28:55 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/03 16:02:22 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include "../header.h"

typedef enum {
    TK_WORD,
	TK_ASSIGN,
    TK_PIPE,
    TK_REDIR_IN, // error if no fd
    TK_REDIR_IN2, // create and read
    TK_REDIR_OUT, //create and write
    TK_REDIR_APPEND, //create and append
    TK_HEREDOC,
}	token_type;

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
void	add_token(t_token **tk, token_type type, char *str, int len);
int		take_word_len(char *str, int i);
t_token	*lex(char *input);
int		input_error(t_token **tk);
int		expand(t_token  **tk);
int		is_redir(t_token *tk);

#endif