/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:17:47 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/19 13:43:16 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	last_redir_in(t_list *lst_redir)
{
	int		is_redirin;
	t_list	*tmp;
	t_redir *redir;

	tmp = lst_redir->next;
	while (tmp)
	{
		redir = tmp->content;
		is_redirin = redir->type == TK_REDIR_IN || redir->type == TK_REDIR_IN2;
		if (redir->type == TK_HEREDOC || is_redirin)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	last_redir_out(t_list *lst_redir)
{
	t_list	*tmp;
	t_redir *redir;

	tmp = lst_redir->next;
	while (tmp)
	{
		redir = tmp->content;
		if (redir->type == TK_REDIR_OUT || redir->type == TK_REDIR_APPEND)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static int	stdin_value(t_list *lst_redir)
{
	int		fd;
	t_redir	*redir;

	fd = STDIN_FILENO;
	if (lst_redir == NULL)
		return (STDIN_FILENO);
	redir = lst_redir->content;
	if (redir->type == TK_REDIR_IN2)
		fd = open(redir->file,  O_RDWR | O_TRUNC |O_CREAT, 0666);
	else
		fd = open(redir->file, O_RDONLY);
	if (!last_redir_in(lst_redir))
		close(fd);
	invalid_fd(fd, redir->file);
	return (fd);
}

static int	stdout_value(t_list *lst_redir)
{
	int		fd;
	t_redir	*redir;

	if (lst_redir == NULL)
		return (STDOUT_FILENO);
	redir = lst_redir->content;
	if (redir->type == TK_REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else
		fd = open(redir->file, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (!last_redir_out(lst_redir))
		close(fd);
	invalid_fd(fd, redir->file);
	return (fd);
}

int	*redir_value(t_list *lst_redir)
{
	int		*fd;
	t_redir	*redir;

	fd = malloc(sizeof(int) * 2);
	if (!fd)
		return (NULL);
	fd[0] = STDIN_FILENO;	
	fd[1] = STDOUT_FILENO;
	while (lst_redir)
	{
		redir = lst_redir->content;
		if (redir->type == TK_REDIR_OUT || redir->type == TK_REDIR_APPEND)
			fd[1] = stdout_value(lst_redir);
		else
		{
			if (redir->type != TK_HEREDOC)
				fd[0] = stdin_value(lst_redir);
		}
		if (fd[0] == -1 || fd[1] == -1)
			return (fd);
		lst_redir = lst_redir->next;
	}
	return (fd);
}
