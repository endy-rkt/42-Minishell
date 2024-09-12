/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:17:47 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/12 12:28:55 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	invalid_fd(int fd, char *file)
{
	if (fd != -1)
		return ;
	ft_putstr_fd("minishell: ", 2);	
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": file descriptor error\n", 2);
	close(fd);
}

static int	handle_invalid_fd(int fd, char *file)
{
	invalid_fd(fd, file);
	return (fd);
}

static int	test_fdin(t_list *lst)
{
	int		fd;
	t_redir	*redir;

	fd = STDIN_FILENO;
	redir = lst->content;
	if (redir->type == TK_REDIR_IN2)
		fd = open(redir->file, O_RDWR | O_CREAT, 0777);
	else
		fd = open(redir->file, O_RDONLY);
	close(fd);
	invalid_fd(fd, redir->file);
	return (fd);
}

int	handle_stdin(t_)
{
	int		fd;
	t_redir	*redir;
	t_list	*lst_redir;

	lst_redir = cmd->redir_in;
	fd = STDIN_FILENO;
	if (lst_redir == NULL)
		return (STDIN_FILENO);
	last_redir = ft_lstlast(lst_redir);
	while (lst_redir != last_redir)
	{
		fd = test_fdin(lst_redir);
		if (fd == -1)
			return (fd);
		lst_redir = lst_redir->next;
	}
	redir = last_redir->content;
	if (redir->type == TK_REDIR_IN2)
		fd = open(redir->file,  O_RDWR | O_TRUNC |O_CREAT, 0777);
	else if (redir->type == TK_REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	invalid_fd(fd, redir->file);
	return (fd);
}

int	handle_stdout(t_list *lst_redir)
{
	int		fd;
	t_redir	*redir;

	if (lst_redir == NULL)
		return (STDOUT_FILENO);
	redir = lst_redir->content;
	if (last_redir_out(lst_redir))
	{
		fd = open(redir->file, O_WRONLY | O_CREAT, 0777);
		close(fd);
	}
	else
	{
		if (redir->type == TK_REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		else
			fd = open(redir->file, O_WRONLY | O_APPEND | O_CREAT, 0777);	
	}
	invalid_fd(fd, redir->file);
	return (fd);
}

int	*redir_value(t_cmd *cmd)
{
	int		*fd;
	t_redir	*redir;
	t_list	*lst_redir;

	fd = malloc(sizeof(int) * 2);
	if (!fd)
		return (NULL);
	fd[0] = STDIN_FILENO;	
	fd[1] = STDOUT_FILENO;
	lst_redir = cmd->redir;
	while (lst_redir)
	{
		redir = lst_redir->content;
		if (redir->type == TK_REDIR_OUT || redir->type == TK_REDIR_APPEND)
			fd[0] = handle_stdout(lst_redir);
		else
			fd[1] = handle_stdin(lst_redir);
		if (fd[0] == -1 || fd[1] == -1)
			return (fd);
		lst_redir = lst_redir->next;
	}
	return (fd);
}
