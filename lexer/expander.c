/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:27:04 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/13 00:08:52 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	expand_word(t_token	**tk)
{

}

void	expand_redir(t_token **tk)
{
	int		i;
	char	*tmp;
	char	*value;

	tmp = (*tk)->value;
	while (tmp[i] == '0')
		i++;
	value = ft_substr(tmp + i, 0, ft_strlen(tmp + i) + 1);
	free(tmp);
	while (ft_isdigit(value[i]))
		i++;
	
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
	if(input_error(*tk))
		tk_clear(tk);
}
