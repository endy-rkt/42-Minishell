/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:21:00 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/02 12:15:35 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int handle_operator(char *str, int i, t_token **tk)
{

}

int	handle_simple_char(char *str, int i, t_token **tk)
{

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
	while (input[i])
	{
		if (is_operator(input[i]))
			i += handle_operator(str, i, &tk);
		else
			i += handle_simple_char(str, i, &tk);
	}
	free(str);
	return (tk);
}
