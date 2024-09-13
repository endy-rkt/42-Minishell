/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:47:54 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/13 13:27:41 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	handle_pipe(char *str, t_token **tk)
{
	int	len;

	len = 1;
	add_token(tk, TK_PIPE, str, len);
	return (len);
}

static int	handle_single_redir(char *str, t_token **tk, int len)
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

static int	handle_redir(char *str, t_token **tk, int len)
{
	int	len;
	int	redir_nb;

	len  = 0;
	redir_nb = 0;
	while (str[len] == '<' || str[len] == '>')
	{
		len++;
		redir_nb++;
	}
	if (redir_nb == 1)
		return (handle_single_redir(str, tk, len));
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

int	handle_operator(char *str, t_token **tk)
{
	int	len;

	len = 0;
	if (str[len] == '|')
		len += handle_pipe(str, tk);
	else
		len += handle_redir(str, tk, len);
	return (len);
}
