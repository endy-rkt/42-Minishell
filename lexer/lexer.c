/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:21:00 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/02 11:35:30 by trazanad         ###   ########.fr       */
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
	t_token	*tk;

	tk = NULL;
	i = 0;
	while (ft_isspace(input[i]))
		i++;
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
	return (tk);
}
