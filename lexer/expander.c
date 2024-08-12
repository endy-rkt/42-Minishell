/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:27:04 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/12 17:17:17 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//if begin with wilcard then error
int	expand_word(t_token **tk)
{
	char	*value;

	value = (*tk)->value;
}

int	expand_pipe(t_token **tk)
{
	if (!(*tk)->prev)
		return (1);
	if ((*tk)->next)
	{
		if ((*tk)->next->type == TK_PIPE || (*tk)->next->type == TK_OR || (*tk)->next->type == TK_AND 
			|| (*tk)->next->type == TK_R_PAREN || (*tk)->next->type == TK_WILDCARD || (*tk)->next->type == TK_SEMICOLON)
			return (1);
	}
	return (0);
}

//if last token is redir not heredoc then error
int	expand_redir(t_token **tk)
{
	
}

int	expand_or_and(t_token **tk)
{
	if (!(*tk)->prev)
		return (1);
	if ((*tk)->next)
	{
		if ((*tk)->next->type == TK_PIPE || (*tk)->next->type == TK_OR || (*tk)->next->type == TK_AND || (*tk)->next->type == TK_WILDCARD)
			return (1);
	}
	return (0);	
}

int	expand_lparen(t_token **tk)
{
	if (!(*tk)->next)
		return (1);
	if ((*tk)->next->type == TK_PIPE || (*tk)->next->type == TK_AND || (*tk)->next->type == TK_OR)
		return (1);
	return (0);	
}

int	expand_rparen(t_token **tk)
{
	if (!(*tk)->prev)
		return (1);
	return (0);	
}

int	expand_token(t_token **tk)
{
	int	error_checked;

	error_checked = 0;
    if ((*tk)->type == TK_PIPE)
		error_checked = expand_pipe(tk);
    else if ((*tk)->type == TK_REDIR)
		error_checked = expand_redir(tk);
    else if ((*tk)->type == TK_L_PAREN)
		error_checked = expand_lparen(tk);
    else if ((*tk)->type == TK_R_PAREN)
		error_checked = expand_rparen(tk);
    else if ((*tk)->type == TK_OR || (*tk)->type == TK_AND)
		error_checked = expand_or_and(tk);
    else;//word
		error_checked = expand_word(tk);
	return (error_checked);
}

/*
	need to clear list if error_checked
*/
int	expand(t_token  **tk)
{
	int	error_checked;

	error_checked = 0;
	if (*tk)
		error_checked = expand_token(tk);
	if ((*tk)->next && !error_checked)
		error_checked = expand(&((*tk)->next));
	return (error_checked);
}

