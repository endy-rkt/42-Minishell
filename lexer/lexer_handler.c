/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:47:54 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/19 12:24:38 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	lex_pipe(char *str, t_token **tk)
{
	int	len;

	len = 1;
	add_token(tk, TK_PIPE, str, len);
	return (len);
}

static int	lex_single_redir(char *str, t_token **tk, int len)
{
	if (str[len - 1] == '>')
	{
		add_token(tk, TK_REDIR_OUT, str, len);
		if (str[len] == '|')
			len++;
	}
	else
		add_token(tk, TK_REDIR_IN, str, len);
	return (len);
}

static int	lex_redir(char *str, t_token **tk, int len)
{
	int	redir_nb;

	redir_nb = 0;
	while (str[len] == '<' || str[len] == '>')
	{
		len++;
		redir_nb++;
	}
	if (redir_nb == 1)
		return (lex_single_redir(str, tk, len));
	if (str[len - 1] == '<' && str[len - 2] == '<')
	{
		if (str[len] == '-')
			len++;
		while (ft_isspace(str[len]))
			len++;
		len += take_word_len(str, len);
		add_token(tk, TK_HEREDOC, str, len);
	}
	else
		add_token(tk, TK_REDIR_APPEND, str, len);
	return (len);
}

int	lex_operator(char *str, t_token **tk)
{
	int	len;

	len = 0;
	if (str[len] == '|')
		len += lex_pipe(str, tk);
	else
		len += lex_redir(str, tk, len);
	return (len);
}
