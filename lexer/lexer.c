/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:21:00 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/16 11:20:37 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	add_token(t_token **tk, token_type type, char *str, int len)
{
	char	*value;
	t_token	*tk_tmp;

	if (len <= 0 || !str)
		return ;
	value = ft_substr(str, 0, len);
	tk_tmp = tk_create(value, type, tk_last(*tk));
	if (!(*tk))
		*tk = tk_tmp;
	else
		tk_last(*tk)->next = tk_tmp;
}

int	take_word_len(char *str, int i)
{
	int	check_in;
	int	tmp;

	check_in = 0;
	while (str[i] && !ft_isspace(str[i]) && !is_operator(str[i]))
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i + 1] == '\0')
				return (check_in + 1);
			else
			{
				tmp = 0;
				tmp += idx_of_first(str + i + 1, str[i]);
				i += tmp;
				check_in += tmp;
			}
		}
		else
		{
			i++;
			check_in++;
		}
	}
	return (check_in);
}

int	handle_operator(char *str, t_token **tk)
{
	int		len;
	int		redir_nb;

	len = 0;
	if (str[len] == '|')
	{
		len++;
		if (str[len] == '|')
		{
			len++;
			add_token(tk, TK_OR, str, len);
		}
		else
			add_token(tk, TK_PIPE, str, len);
	}
	else if (str[len] == '&')
	{
		len++;
		if (str[len] == '&')
		{
			len++;
			add_token(tk, TK_AND, str, len);
		}
		else
		{
			len += take_word_len(str, len);//	
			add_token(tk, TK_WORD, str, len);
		}
	}
	else if (ft_strchr("()", str[len]))
	{
		if (str[len] == '(')
			add_token(tk, TK_L_PAREN, str, 1);
		else
			add_token(tk, TK_R_PAREN, str, 1);
		len++;
	}
	else if (str[len] == ';')
	{
		len++;
		add_token(tk, TK_SEMICOLON, str, len);
	}
	else
	{
		redir_nb = 0;
		while (str[len] == '<' || str[len] == '>')
		{
			len++;
			redir_nb++;
		}
		if (redir_nb == 1)
		{
			if (str[len - 1] == '>')
				add_token(tk, TK_REDIR_OUT, str, len);
			else
				add_token(tk, TK_REDIR_IN, str, len);
			return (len);
		}
		if (str[len - 1] == '<' && str[len - 2] == '<')
		{
			if (str[len] == '-')
				len++;
			while (ft_isspace(str[len]))
				len++;
			len += take_word_len(str, len);//
			add_token(tk, TK_HEREDOC, str, len);
		}
		else
			add_token(tk, TK_REDIR_OUT2, str, len);
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
	if (redir_nb == 1)
	{
		if (str[len - 1] == '>')
		add_token(tk, TK_REDIR_OUT, str, len);
		else
		add_token(tk, TK_REDIR_IN, str, len);
		return (len);
	}
	if (redir_nb == 0)
	{
		len += take_word_len(str, len);
		add_token(tk, TK_WORD, str, len);
		return (len);
	}
	if (str[len - 1] == '<' && str[len - 2] == '<')
	{
		if (str[len] == '-')
			len++;
		while (ft_isspace(str[len]))
			len++;
		len += take_word_len(str, len);//
		add_token(tk, TK_HEREDOC, str, len);
	}
	else
		add_token(tk, TK_REDIR_OUT2, str, len);
	return (len);
}

int	handle_char(char *str, t_token **tk)
{
	int		len;

	len = 0;
	len += take_word_len(str, len);
	add_token(tk, TK_WORD, str, len);
	return (len);
}

int	create_tk_list(char *str, t_token **tk)
{
	int	len;

	len = 0;
	while (ft_isspace(str[len]))
		len++;
	if (str[len] == '\0')
		return (0);
	if (is_operator(str[len]))
		len += handle_operator(str + len, tk);
	else if (ft_isdigit(str[len]))
		len += handle_digit(str + len, tk);
	else
		len += handle_char(str + len, tk);
	return (len);
}

t_token	*lex(char *input)
{
	int		i;
	char	*str;
	t_token	*tk;

	if (input[0] == '\n')
		return (NULL);
	if ((input[0] == '\'' || input[0] == '\"') && input[1] == '\0')
		return (NULL); //error
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
