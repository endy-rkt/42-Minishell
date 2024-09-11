/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:16:41 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 16:22:01 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	add_redir(t_token **tk, t_cmd **cmd, int fd, int type)
{
	t_redir	*redir;

	if (!is_redir(*tk))
		return (0);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (0);
	redir->fd = fd;
	redir->type = type;
	*tk = (*tk)->next;
	redir->file = NULL;
	if ((*tk) != NULL && ((*tk)->type == TK_WORD || (*tk)->type == TK_ASSIGN))
		redir->file = ft_strdup((*tk)->value);
	if (type == TK_REDIR_OUT || type == TK_REDIR_APPEND)
		ft_lstadd_back(&((*cmd)->redir_out), ft_lstnew(redir));
	else
		ft_lstadd_back(&((*cmd)->redir_in), ft_lstnew(redir));
	return (1);
}

int	take_redir(t_token **tk, t_cmd **cmd)
{
	int		fd;
	int		type;
	int		status;
	char	*value;

	fd = 0;
	type = (*tk)->type;
	value = (*tk)->value;
	if (type == TK_REDIR_OUT || type == TK_REDIR_APPEND)
		fd = 1;
	if (ft_isdigit(value[0]))
		fd = ft_atoi(value);
	status = add_redir(tk, cmd, fd, type);
	return (status);
}

int	take_heredoc(t_token **tk, t_cmd **cmd)
{
	int		i;
	char	*tk_value;
	t_redir	*heredoc;
	int		tmp_fd;

	if ((*tk)->type != TK_HEREDOC)
		return (0);
	heredoc = malloc(sizeof(t_redir));
	if (!heredoc)
		return (0);
	i = 0;
	tk_value = (*tk)->value;
	tmp_fd = 0;
	if (ft_isdigit(tk_value[i]))
		tmp_fd = ft_atoi(tk_value);
	while (ft_isdigit(tk_value[i]) || tk_value[i] == '<')
		i++;
	heredoc->fd = tmp_fd;
	heredoc->file = ft_strdup(tk_value + i);
	heredoc->type = TK_HEREDOC;
	ft_lstadd_back(&((*cmd)->redir_in), ft_lstnew(heredoc));
	return (1);
}

int	take_assign(t_token **tk, t_cmd **cmd)
{
	char	*value;

	if ((*tk)->type != TK_ASSIGN)
		return (0);
	value = ft_strdup((*tk)->value);
	ft_lstadd_back(&((*cmd)->assign), ft_lstnew(value));
	return (1);
}

int	take_args(t_token **tk, t_cmd **cmd, int arg)
{
	char	**args;

	if ((*tk)->type != TK_ASSIGN && (*tk)->type != TK_WORD)
		return (0);
	(*cmd)->args[arg] = ft_strdup((*tk)->value);
	return (1);
}
