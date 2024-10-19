/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:38:39 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/19 12:25:45 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*join_char(char *new_value, char c)
{
	char	*tmp;
	char	*str;

	tmp = malloc(2);
	if (!tmp)
		return (NULL);
	tmp[0] = c;
	tmp[1] = '\0';
	str = ft_strjoin(new_value, tmp);
	free(tmp);
	return (str);
}

int	expand_single_quote(char *value, char **new_value, int i)
{
	i++;
	while (value[i] && value[i] != '\'')
	{
		*new_value = join_char(*new_value, value[i]);
		i++;
	}
	if (value[i] == '\'')
		i++;
	return (i);
}

int	expand_double_quote(char *value, char **new_value, int i, t_sh_params *shell_params)
{
	i++;
	while (value[i] && value[i] != '\"')
	{
		if (value[i] == '$')
		{
			if (value[i + 1] == '\'')
				*new_value = ft_strjoin(*new_value, "$");
			i = expand_params(value, new_value, i, shell_params);
		}
		else
		{
			*new_value = join_char(*new_value, value[i]);
			i++;
		}
	}
	if (value[i] == '\"')
		i++;
	return (i);
}
