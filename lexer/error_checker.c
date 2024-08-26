/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:46:18 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/26 10:05:40 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	redir_out2_to_in2(t_token **tk)
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

int	redir_out2_error(t_token **tk)
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
	if (redir_nb > 2 || redir_value[1] == '<')
		return (1);
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

int	heredoc_error(t_token **tk)
{
	int		i;
	int		redir_nb;
	char	*value;

	i = 0;
	redir_nb = 0;
	value = (*tk)->value;
	while (ft_isdigit(value[i]))
		i++;
	while (value[i] == '<' || value[i] == '>')
	{
		if (value[i] == '>')
			return (1);
		i++;
		redir_nb++;
	}
	if (redir_nb > 2 || !value[i])
		return (1);
	return (0);
}

int	pipe_error(t_token **tk)
{
	if (!(*tk)->prev)
		return (1);
	if ((*tk)->next)
	{
		if ((*tk)->next->type == TK_PIPE)
			return (1);
	}
	return (0);
}

int	input_error(t_token **tk)
{
	int	error_checked;

	error_checked = 0;
    if ((*tk)->type == TK_PIPE)
		error_checked = pipe_error(tk);
    else if (is_redir(*tk))
		error_checked = redir_error(tk);
	else if ((*tk)->type == TK_HEREDOC)
		error_checked = heredoc_error(tk);
	if (!error_checked && (*tk)->next)
		return (input_error(&((*tk)->next)));
	return (error_checked);
}
