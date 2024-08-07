/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 08:51:18 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/07 15:26:05 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '&' || c == '*');
}

int	idx_of_last(char *str, char c)
{
	int len;

	len = ft_strlen(str) - 1;
	if (len < 0)
		return (-1);
	while (str[len])
	{
		if (str[len] == c)
			return (len);
		len--;
	}
	return (0);
}

int	idx_of_first(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (i + 1);
		i++;
	}
	return (1);
}
