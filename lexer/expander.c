/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:27:04 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/14 11:15:46 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	expand_word(t_token	**tk)
{

}

// void	no_quote_delimiter(char *value, char *new_value, int i)
// {
// 	char	tmp;

// 	tmp = 0;
// 	while (value[i])
// 	{
// 		if ((value[i] == '\'' || value[i] == '\"') && tmp == 0)
// 			tmp = value[i];
// 		else if (value[i] == tmp && tmp != 0)
// 			tmp = 0;
// 		else
// 			new_value[i] = value[i];
// 		i++;
// 	}
// 	new_value[i] = '\0';
// }

int	format_delimiter(char *value, char *new_value, int i, int j)
{
	char	tmp;

	tmp = 0;
	if (value[i] == '-')
		i++;
	while (ft_isspace(value[i]))
		i++;
	while (value[i])
	{
		if ((value[i] == '\'' || value[i] == '\"') && tmp == 0)
			tmp = value[i];
		else if (value[i] == tmp && tmp != 0)
			tmp = 0;
		else
		{
			new_value[j] = value[i];
			j++;
		}
		i++;
	}
	return (j);
}

void	expand_redir(t_token **tk)
{
	int		i;
	int		j;
	char	*value;
	char	*new_value;

	i = 0;
	j = 0;
	value = (*tk)->value;
	while (value[i] == '0')
		i++;
	new_value = malloc(ft_strlen(value) + 1);
	while ((ft_isdigit(value[i]) || value[i] == '>' || value[i] == '<') && value[i])
	{
		new_value[j] = value[i];
		i++;
		j++;
	}
	if ((*tk)->type == TK_HEREDOC)
		j = format_delimiter(value, new_value, i, j);
	new_value[j] = '\0';
	free(value);
	(*tk)->value = new_value;
}

void	expand_token(t_token **tk)
{
	if (*tk)
	{
		if ((*tk)->type == TK_WORD)
			expand_word(tk);
		if ((*tk)->type == TK_REDIR_IN || (*tk)->type == TK_REDIR_OUT 
			|| (*tk)->type == TK_REDIR_OUT2  || (*tk)->type == TK_HEREDOC)
			expand_redir(tk);
		if ((*tk)->next)
			expand_token(&((*tk)->next));
	}
}

void	expand(t_token  **tk)
{
	if (!*tk)
		return ;
	expand_token(tk);
	// if(input_error(*tk))
	// 	tk_clear(tk);
}
