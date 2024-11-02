/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:18:54 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/02 14:23:32 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	redir_out2_to_in2(t_token **tk)
{
	int		i;
	char	*value;
	char	*new_value;

	i = 0;
	value = (*tk)->value;
	new_value = malloc(ft_strlen(value) + 1);
	if (!new_value)
		return ;
	new_value[i] = '<';
	i++;
	new_value[i] = '\0';
	free(value);
	(*tk)->value = new_value;
	(*tk)->type = TK_REDIR_IN2;
}

static int	redir_out2_error(t_token **tk)
{
	int		i;
	int		redir_nb;
	char	*redir_value;
	char	*value;

	i = 0;
	redir_nb = 0;
	value = (*tk)->value;
	redir_value = value + i;
	while (value[i] == '>' || value[i] == '<')
	{
		i++;
		redir_nb++;
	}
	if (redir_value[1] == '<')
		return (my_perror(2,
				"minishell: syntax error near unexpected token `<'\n"));
	if (redir_nb > 2)
		return (my_perror(2,
				"minishell: syntax error near unexpected token `>'\n"));
	if (redir_value[0] == '<' && redir_value[1] == '>')
		redir_out2_to_in2(tk);
	return (0);
}

int	redir_error(t_token **tk)
{
	if ((*tk)->next == NULL || (*tk)->next->value == NULL)
		return (my_perror(2,
				"minishell: syntax error near unexpected token `<'\n"));
	if (is_redir((*tk)->next) || (*tk)->next->type == TK_HEREDOC
		|| (*tk)->next->type == TK_PIPE)
		return (my_perror(2,
				"minishell: syntax error near unexpected token `<'\n"));
	if ((*tk)->type == TK_REDIR_APPEND)
		return (redir_out2_error(tk));
	return (0);
}
