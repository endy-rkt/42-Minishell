/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:28:55 by trazanad          #+#    #+#             */
/*   Updated: 2024/07/30 10:16:46 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include "../header.h"

typedef enum {
    TK_CMD,
    TK_WORD,
    TK_PIPE,
	TK_QUOTED,
    TK_REDIR_IN,
    TK_REDIR_OUT,
    TK_REDIR_OUT2,
    TK_HDOC_START,
    TK_HDOC_END,
    TK_HDOC_TXT,
} token_type;

typedef struct s_token
{
	token_type	type;
	char		*value;
}	t_token;

#endif