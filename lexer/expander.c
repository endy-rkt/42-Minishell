/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:27:04 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/12 11:37:42 by trazanad         ###   ########.fr       */
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
    t_token **tk_tmp;

    if (!*tk)
        return ;
    expand_token(tk);
    *tk_tmp = (*tk)->next;
    while (*tk_tmp)
    {
        expand_token(tk_tmp);
        *tk_tmp = (*tk_tmp)->next;
    }
}

