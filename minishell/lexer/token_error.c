/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:11:30 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 15:20:14 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	my_perror(int status, char *str)
{
	ft_putstr_fd(str, 2);
	return (status);
}

static int	heredoc_error(t_token **tk)
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
		return (my_perror(2, "minishell: syntax error near unexpected token `<'"));
	return (0);
}

static int	pipe_error(t_token **tk)
{
	if (!(*tk)->prev)
		return (my_perror(2, "minishell: syntax error near unexpected token `|'"));
	if ((*tk)->next)
	{
		if ((*tk)->next->type == TK_PIPE)
			return (my_perror(2, "minishell: syntax error near unexpected token `|'"));
	}
	return (0);
}

int	check_tk_error(t_token **tk, t_sh_params **sh_params)
{
	int	error_status;

	error_status = 0;
    if ((*tk)->type == TK_PIPE)
		error_status = pipe_error(tk);
    else if (is_redir(*tk))
		error_status = redir_error(tk);
	else if ((*tk)->type == TK_HEREDOC)
		error_status = heredoc_error(tk);
	if (!error_status && (*tk)->next)
		return (check_tk_error(&((*tk)->next), sh_params));
	if (error_status != 0)
		(*sh_params)->exit_status = error_status;
	return (error_status);
}
