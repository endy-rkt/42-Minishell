/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:17:47 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/18 08:47:26 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

static void	print_error(char *arg_name, char *message)
{
	char	*str;

	str = ft_strdup(arg_name);
	str = ft_strjoin(str, ":");
	str = ft_strjoin(str, message);
	ft_putstr_fd(str, 2);
	free(str);
}

static void	invalid_fd(int fd, char *file)
{
	if (fd != -1)
		return ;
	// ft_putstr_fd("minishell: ", 2);
	// ft_putstr_fd(file, 2);
	if (access(file, F_OK))
		// ft_putstr_fd(": No such file or directory\n", 2);
		print_error(file, " No such file or directory\n");
	else if (access(file, R_OK | W_OK))
		// ft_putstr_fd(": Permission denied\n", 2);
		print_error(file, " Permission denied\n");

	close(fd);
}

static int	handle_stdin(t_list *lst_redir)
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

static int	handle_stdout(t_list *lst_redir)
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
			fd[1] = handle_stdout(lst_redir);
		else
		{
			if (redir->type != TK_HEREDOC)
				fd[0] = handle_stdin(lst_redir);
		}
		if (fd[0] == -1 || fd[1] == -1)
			return (fd);
		lst_redir = lst_redir->next;
	}
	return (fd);
}
