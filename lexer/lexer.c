/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:21:00 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/02 12:11:49 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int handle_operator(char *str, t_token **tk)
{

}

int	handle_simple_char(char *str, t_token **tk)
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
	tk = NULL;
	i = 0;
	while (input[i])
	{
		if (is_operator(input[i]))
		{
			//handle_operator
		}
		else
		{
			//handle_non_operator
		}
	}
	free(str);
	return (tk);
}
