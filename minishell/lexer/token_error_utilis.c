/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_utilis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:18:54 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 15:20:38 by trazanad         ###   ########.fr       */
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
	while (ft_isdigit(value[i]))
	{
		new_value[i] = value[i];
		i++;
	}
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
	while (ft_isdigit(value[i]))
		i++;
	redir_value = value + i;
	while (value[i] == '>' || value[i] == '<')
	{
		i++;
		redir_nb++;
	}
	if (redir_value[1] == '<')
		return (my_perror(2, "minishell: syntax error near unexpected token `<'"));
	if (redir_nb > 2)
		return (my_perror(2, "minishell: syntax error near unexpected token `>'"));
	if (redir_value[0] == '<' && redir_value[1] == '>')
		redir_out2_to_in2(tk);
	return (0);
}

int	redir_error(t_token **tk)
{
	int		i;
	int		redir_nb;
	char	*value;

	if (!(*tk)->next)
		return (1);
	if (is_redir((*tk)->next) || (*tk)->next->type == TK_HEREDOC || (*tk)->next->type == TK_PIPE)
		return (1);
	if ((*tk)->type == TK_REDIR_APPEND)
		return (redir_out2_error(tk));
	return (0);
}
