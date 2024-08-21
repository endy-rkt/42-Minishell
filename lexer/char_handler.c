/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 08:51:18 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/21 23:20:56 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_operator(char c)
{
	if (ft_strchr("<>|", c)) //()&;
		return (1);
	return (0);
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

	i = 0;
	if (str[0] == 0)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i + 2);
		i++;
	}
	return (1);
}
