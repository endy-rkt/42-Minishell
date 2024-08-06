/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:21:00 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/06 14:54:27 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	add_token(t_token **tk, token_type type, char *str, int len)
{
	char	*value;
	t_token	*tk_tmp;

	value = ft_substr(str, 0, len);
	tk_tmp = tk_create(value, type, tk_last(*tk));
	tk_last(*tk)->next = tk_tmp;
}

int	take_word_len(char *str, int i)
{
	while (str[i] && !ft_isspace(str[i]) && !is_operator(str[i]))
	{
		while (str[i] != '\'' && str[i] != '\"' && str[i])
			i++;
		if (str[i] == '\'' || str[i] == '\"')
			i += idx_of_first(str + i, str[i]);
	}
	return (i);
}

int	handle_operator(char *str, t_token **tk)
{
	int		len;

	len = 0;
	if (str[len] == '|')
	{
		if (str[len + 1] == '|')
			add_token(&tk, TK_OR, str, len + 2);
		else
			add_token(&tk, TK_PIPE, str, len + 1);
	}
	else if (str[len] == '&')
	{
		if (str[len + 1] == '&')
			add_token(&tk, TK_AND, str, len + 2);
		else
		{
			len++;
			len += take_word_len(str, len);	
			add_token(&tk, TK_WORD, str, len);
		}
	}
	else
	{
		while (str[len] == '<' || str[len] == '>')
			len++;
		len += take_word_len(str, len);
		add_token(&tk, TK_REDIR, str, len);
	}
	return (len);
}

int	handle_digit(char *str, t_token **tk)
{
	int		len;
	int		redir_nb;

	len = 0;
	redir_nb = 0;
	while (ft_isdigit(str[len]))
		len++;
	while (str[len] == '<' || str[len] == '>')
	{
		len++;
		redir_nb++;
	}
	len += take_word_len(str, len);
	if (redir_nb == 0)
		add_token(&tk, TK_WORD, str, len);
	else
		add_token(&tk, TK_REDIR, str, len);
	return (len);
}

int	handle_char(char *str, t_token **tk)
{
	int		len;
	char	*value;
	t_token	*tk_tmp;

	len = 0;
	len += take_word_len(str, len);
	add_token(&tk, TK_WORD, str, len);
	return (len);
}

int	create_tk_list(char *str, t_token **tk)
{
	int	len;

	if (is_operator(str[0]))
		len += handle_operator(str, tk);
	else if (ft_isdigit(str[0]))
		len += handle_digit(str, tk);
	else
		len += handle_char(str, tk);
	return (len);
}

t_token	*lex(char *input)
{
	int		i;
	char	*str;
	t_token	*tk;

	str = ft_retire_space(input);
	if (!str)
		return (NULL);
	i = 0;
	tk = NULL;
	while (str[i])
		i += create_tk_list(str + i, &tk);
	free(str);
	return (tk);
}
