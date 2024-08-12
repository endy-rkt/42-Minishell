/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:27:04 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/12 12:44:52 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void    expand_token(t_token **tk)
{
    if ((*tk)->type == TK_PIPE);
    else if ((*tk)->type == TK_REDIR);
    else if ((*tk)->type == TK_L_PAREN);
    else if ((*tk)->type == TK_R_PAREN);
    else if ((*tk)->type == TK_OR || (*tk)->type == TK_AND);
    else;//word
}

void    expand(t_token  **tk)
{
	if (*tk)
		expand_token(tk);
	if ((*tk)->next)
		expand(&((*tk)->next));
}

