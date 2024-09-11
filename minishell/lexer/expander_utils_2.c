/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:01:07 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 16:05:40 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*my_getenv(char *var, t_sh_params *sh_params)
{
	char	*str;

	if (!var)
		return ("");
	str = getenv(var);
	if (!str)
		return ("");
	return (str);
}

static int	error_status(char *value, char **new_value, int i, t_sh_params *sh_params)
{
	char	*prev_error;

	prev_error = ft_itoa(sh_params->exit_status);
	*new_value = ft_strjoin(*new_value, prev_error);
	free(prev_error);
	return (i + 1);
}

static int	void_expansion(char *value, char **new_value, int i, char *str)
{
	*new_value = ft_strjoin(*new_value, str);
	return (i + 1);
}

static int	not_alpha_expansion(char *value, char **new_value, int i)
{
	char	*tmp;

	tmp = ft_strdup("$");
	tmp = join_char(tmp, value[i]);
	*new_value = ft_strjoin(*new_value, tmp);
	free(tmp);
	return (i + 1);
}

int	expand_params(char *value, char **new_value, int i, t_sh_params *sh_params)
{
	char	*tmp;

	i++;
	if (value[i] == '\'' || value[i] == '\"')
		return (i);
	else if (value[i] == '\0' || ft_isspace(value[i]))
		return (void_expansion(value, new_value, i - 1, "$"));
	else if (value[i] == '?')
		return (error_status(value, new_value, i, sh_params));
	else if (ft_strchr("$!#*@-", value[i]) || ft_isdigit(value[i]))
		return (void_expansion(value, new_value, i, ""));
	else if (!(ft_isalpha(value[i]) || value[i] == '_'))
		return (not_alpha_expansion(value, new_value, i));
	tmp = ft_strdup("");
	while (ft_isalpha(value[i]) || value[i] == '_' || ft_isdigit(value[i]))
	{
		tmp = join_char(tmp, value[i]);
		i++;
	}
	*new_value = ft_strjoin(*new_value, my_getenv(tmp, sh_params));
	free(tmp);
	return (i);
}
