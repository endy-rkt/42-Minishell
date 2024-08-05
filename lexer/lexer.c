/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:21:00 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/06 00:21:45 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	handle_operator(char *str, t_token **tk)
{
	int		len;
	char	*value;
	t_token	*tk_tmp;

	len = 0;
	if (str[len] == '|')
	{
		if (str[len + 1] == '|')
		{
			value = ft_substr(str, 0, len + 1);
			tk_tmp = tk_create(value, TK_OR, tk_last(*tk));
			tk_last(*tk)->next = tk_tmp;
		}
		else
		{
			value = ft_substr(str, 0, len);
			tk_tmp = tk_create(value, TK_PIPE, tk_last(*tk));
			tk_last(*tk)->next = tk_tmp;
		}
	}
	else if (str[len] == '&')
	{
		if (str[len + 1] == '&')
		{
			value = ft_substr(str, 0, len + 1);
			tk_tmp = tk_create(value, TK_AND, tk_last(*tk));
			tk_last(*tk)->next = tk_tmp;
		}
		else
		{
			while (str[len] && !ft_isspace(str[len]) && !is_operator(str[len]))
			{
				while (str[len] != '\'' && str[len] != '\"' && str[len])
					len++;
				if (str[len] == '\'' || str[len] == '\"')
					len += idx_of_first(str + len, str[len]);
			}
			value = ft_substr(str, 0, len + 1);
			tk_tmp = tk_create(value, TK_AND, tk_last(*tk));
			tk_last(*tk)->next = tk_tmp;
		}
	}
	else
	{
		while (str[len] == '<' || str[len] == '>')
			len++;
		while (str[len] && !ft_isspace(str[len]) && !is_operator(str[len]))
		{
			while (str[len] != '\'' && str[len] != '\"' && str[len])
				len++;
			if (str[len] == '\'' || str[len] == '\"')
				len += idx_of_first(str + len, str[len]);
		}
		value = ft_substr(str, 0, len);
		tk_tmp = tk_create(value, TK_REDIR, tk_last(*tk));
		tk_last(*tk)->next = tk_tmp;
	}
	return (len);
}

int	handle_digit(char *str, t_token **tk)
{
	int		len;
	int		redir_nb;
	char	*value;
	t_token	*tk_tmp;

	len = 0;
	redir_nb = 0;
	while (ft_isdigit(str[len]))
		len++;
	while (str[len] == '<' || str[len] == '>')
	{
		len++;
		redir_nb++;
	}
	while (str[len] && !ft_isspace(str[len]) && !is_operator(str[len]))
	{
		while (str[len] != '\'' && str[len] != '\"' && str[len])
			len++;
		if (str[len] == '\'' || str[len] == '\"')
			len += idx_of_first(str + len, str[len]);
	}
	value = ft_substr(str, 0, len);
	if (redir_nb == 0)
		tk_tmp = tk_create(value, TK_WORD, tk_last(*tk));
	else
		tk_tmp = tk_create(value, TK_REDIR, tk_last(*tk));
	tk_last(*tk)->next = tk_tmp;
	return (len);
}

int	handle_char(char *str, t_token **tk)
{
	int		len;
	char	*value;
	t_token	*tk_tmp;

	len = 0;
	while (str[len] && !ft_isspace(str[len]) && !is_operator(str[len]))
	{
		while (str[len] != '\'' && str[len] != '\"' && str[len])
			len++;
		if (str[len] == '\'' || str[len] == '\"')
			len += idx_of_first(str + len, str[len]);
	}
	value = ft_substr(str, 0, len);
	tk_tmp = tk_create(value, TK_WORD, tk_last(*tk));
	tk_last(*tk)->next = tk_tmp;
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
