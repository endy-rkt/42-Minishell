/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:21:48 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/02 18:27:13 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	expand_word(t_token **tk, t_sh_params *shell_params)
{
	int		i;
	char	*value;
	char	*new_value;
	t_list	*lst_word;

	i = 0;
	value = (*tk)->value;
	new_value = ft_strdup("");
	lst_word = NULL;
	while (value[i])
	{
		if (value[i] == '\'')
			i = expand_single_quote(value, &new_value, i);
		else if (value[i] == '\"')
			i = expand_double_quote(value, &new_value, i, shell_params);
		else if (value[i] == '$')
			i += handle_params(&lst_word, value + i, &new_value, shell_params);
		else
		{
			new_value = join_char(new_value, value[i]);
			i++;
		}
	}
	update_tk(tk, &lst_word, &new_value, &value);
}

static void	verify_assign(t_token **tk)
{
	int		i;
	char	*value;

	if (!*tk)
		return ;
	value = (*tk)->value;
	if (value == NULL)
		return ;
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

static void	recursive_expansion(t_token **tk, t_sh_params *shell_params)
{
	if (*tk)
	{
		if ((*tk)->type == TK_WORD || (*tk)->type == TK_ASSIGN)
		{
			if ((*tk)->value)
			{
				verify_assign(tk);
				expand_word(tk, shell_params);
			}
		}
		if ((*tk)->type == TK_E_WORD)
			(*tk)->type = TK_WORD;
		if (is_redir(*tk))
			expand_redir(tk);
		if ((*tk)->next)
			recursive_expansion(&((*tk)->next), shell_params);
	}
}

void	expand(t_token **tk, t_sh_params *shell_params)
{
	if (!tk || (*tk) == NULL)
		return ;
	recursive_expansion(tk, shell_params);
}
