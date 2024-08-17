/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:46:18 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/17 09:32:42 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


// //if begin with wilcard then error
// int	expand_word(t_token *tk)
// {
// 	char	*value;

// 	value = tk->value;
// }

int	pipe_error(t_token *tk)
{
	if (!tk->prev)
		return (1);
	if (tk->next)
	{
		if (tk->next->type == TK_PIPE || tk->next->type == TK_OR || tk->next->type == TK_AND) //|| tk->next->type == TK_R_PAREN || tk->next->type == TK_SEMICOLON
			return (1);
	}
	return (0);
}

//if last token is redir not heredoc then error
int	redir_error(t_token *tk)//
{
	
}

int	heredoc_error(t_token *tk)
{
	
}

int	or_and_error(t_token *tk)
{
	if (!tk->prev)
		return (1);
	if (tk->next)
	{
		if (tk->next->type == TK_PIPE || tk->next->type == TK_OR 
			|| tk->next->type == TK_AND) //|| tk->next->type == TK_SEMICOLON
			return (1);
	}
	return (0);	
}

// int	lparen_error(t_token *tk)
// {
// 	if (!tk->next)
// 		return (1);
// 	if (tk->next->type == TK_PIPE || tk->next->type == TK_AND 
// 		|| tk->next->type == TK_OR || tk->next->type == TK_SEMICOLON)
// 		return (1);
// 	return (0);	
// }

// int	rparen_error(t_token *tk)
// {
// 	if (!tk->prev)
// 		return (1);
// 	return (0);	
// }

int	input_error(t_token *tk)
{
	int	error_checked;

	error_checked = 0;
    if (tk->type == TK_PIPE)
		error_checked = pipe_error(tk);
    else if (tk->type == TK_REDIR_IN || tk->type == TK_REDIR_OUT 
			|| tk->type == TK_REDIR_OUT2)//
		error_checked = redir_error(tk);
	else if (tk->type == TK_HEREDOC)
		error_checked = heredoc_error(tk);
    // else if (tk->type == TK_L_PAREN)
	// 	error_checked = lparen_error(tk);
    // else if (tk->type == TK_R_PAREN)
	// 	error_checked = rparen_error(tk);
    else if (tk->type == TK_OR || tk->type == TK_AND)
		error_checked = or_and_error(tk);
	if (!error_checked && tk->next)
		return (input_error(tk->next));
	return (error_checked);
}
