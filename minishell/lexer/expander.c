/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:21:48 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 15:45:57 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	verify_assign(t_token **tk)
{
	int		i;
	char	*value;

	value = (*tk)->value;
	if (!ft_strchr(value, '='))
		return ;
	i = 0;
	if (ft_isdigit(value[i]) || value[0] == '=')
		return ;
	while (value[i] && value[i] != '=')
	{
		if (!(ft_isalnum(value[i]) || value[i] == '_'))
			return ;
		i++;
	}
	(*tk)->type = TK_ASSIGN;
}

static void	expand_word(t_token	**tk, t_sh_params *sh_params)
{
	int		i;
	char	*value;
	char	*new_value;

	i = 0;
	value = (*tk)->value;
	new_value = ft_strdup("");
	while (value[i])
	{
		if (value[i] == '\'')
			i = expand_single_quote(value, &new_value, i);
		else if (value[i] == '\"')
			i = expand_double_quote(value, &new_value, i, sh_params);
		else if (value[i] == '$')
			i = expand_params(value, &new_value, i, sh_params);
		else
		{
			new_value = join_char(new_value, value[i]);
			i++;
		}
	}
	free(value);
	(*tk)->value = new_value;
}

static void	expand_redir(t_token **tk)
{
	int		i;
	int		j;
	char	*value;
	char	*new_value;

	i = 0;
	j = 0;
	value = (*tk)->value;
	new_value = malloc(ft_strlen(value) + 1);
	if (!new_value)
		return ;
	while (ft_strchr("<>", value[i]) && value[i])
	{
		new_value[j] = value[i];
		i++;
		j++;
	}
	new_value[j] = '\0';
	free(value);
	(*tk)->value = new_value;
}

static void	expand_token(t_token **tk, t_sh_params *sh_params)
{
	if (*tk)
	{
		if ((*tk)->type == TK_WORD || (*tk)->type == TK_ASSIGN)
		{
			verify_assign(tk);
			expand_word(tk, sh_params);
		}
		if (is_redir(*tk))
			expand_redir(tk);
		if ((*tk)->next)
			expand_token(&((*tk)->next), sh_params);
	}
}

void	expand(t_token **tk, t_sh_params *sh_params)
{
	if (!tk || (*tk) == NULL)
		return ;
	expand_token(tk, sh_params);
}
