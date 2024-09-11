/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:35:10 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 15:08:44 by trazanad         ###   ########.fr       */
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

static int	handle_char(char *str, t_token **tk)
{
	int		len;

	len = 0;
	len += take_word_len(str, len);
	add_token(tk, TK_WORD, str, len);
	return (len);
}

static int	create_tk_list(char *str, t_token **tk)
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

t_token	*lex(char *input, t_sh_params **sh_params)
{
	int		i;
	char	*str;
	t_token	*tk;

	if (input[0] == '\n')
		return (NULL);
	if ((input[0] == '\'' || input[0] == '\"') && input[1] == '\n')
	{
		ft_putstr_fd("Error: invalid input\n", 2);
		(*sh_params)->exit_status = 2; //
		return (NULL);
	}
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
