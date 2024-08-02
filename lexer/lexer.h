/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:28:55 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/02 09:34:16 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include "../header.h"

typedef enum {
    TK_WORD,
    TK_PIPE,
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



#endif