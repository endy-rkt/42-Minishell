/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:01:49 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/03 17:50:22 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	free_ast(t_ast **ast)
{
	
}

void	launch_heredoc(t_redir *rd)
{
	int		i;
	char	*delimiter;
	char	*input;

	i = 0;
	delimiter = rd->file;
	while (delimiter[i] == '<' || ft_isdigit(delimiter[i]))
		i++;
	delimiter = delimiter + i;
	printf("delimiter:%s\n", delimiter);
	while (1)
	{
		input = NULL;
		ft_printf("heredoc>");
		input = get_next_line(0);
		if (ft_strncmp(input, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		free(input);
	}
}

int	handle_heredoc(t_redir *rd)
{
	int		i;
	char	*delimiter;
	char	*input;
	char	*value;
	int		fd;

	i = 0;
	delimiter = rd->file;
	while (delimiter[i] == '<' || ft_isdigit(delimiter[i]))
		i++;
	delimiter = delimiter + i;
	fd = open(".hdoc_tmp", O_RDWR | O_TRUNC |O_CREAT, 0777);
	value = ft_strdup("");
	while (1)
	{
		input = NULL;
		ft_printf("heredoc>");
		input = get_next_line(0);
		if (ft_strncmp(input, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		value = ft_strjoin(value, input);
		free(input);
	}
	write(fd, value, ft_strlen(value));
	free(value);
	close(fd);
	return (fd);
}

int	fd_stdin(t_cmd *cmd)
{
	int		fd;
	t_list	*lst_redir;
	t_list	*last_redir;
	t_redir *rd;

	lst_redir = cmd->redir_in;
	fd = STDIN_FILENO;
	if (lst_redir == NULL)
		return (STDIN_FILENO);
	last_redir = ft_lstlast(lst_redir);
	while (lst_redir != last_redir)
	{
		rd = lst_redir->content;
		if (rd->type == TK_HEREDOC)
			launch_heredoc(rd);
		else if (rd->type == TK_REDIR_IN2)
		{
			fd = open(rd->file,  O_RDWR | O_CREAT, 0777);
			close(fd);
		}
		else
		{
			fd = open(rd->file, O_RDONLY);
			if (fd == -1)
				exit(EXIT_FAILURE);
			close(fd);
		}
		lst_redir = lst_redir->next;
	}
	rd = last_redir->content;
	if (rd->type == TK_REDIR_IN2)
		fd = open(rd->file,  O_RDWR | O_TRUNC |O_CREAT, 0777);
	else if (rd->type == TK_REDIR_IN)
	{
		fd = open(rd->file, O_RDONLY);
		if (fd == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		handle_heredoc(rd);
		fd = open(".hdoc_tmp", O_RDONLY, 0777);
	}
	printf("fd=%d\n",fd);
	return (fd);// to close after
}

int	fd_stdout(t_cmd *cmd)
{
	int		fd;
	t_list	*lst_redir;
	t_list	*last_redir;
	t_redir *rd;

	lst_redir = cmd->redir_out;
	if (lst_redir == NULL)
		return (STDOUT_FILENO);
	last_redir = ft_lstlast(lst_redir);
	while (lst_redir != last_redir)
	{
		rd = lst_redir->content;
		fd = open(rd->file,  O_WRONLY | O_CREAT, 0777);
		close(fd);
		lst_redir = lst_redir->next;
	}
	rd = last_redir->content;
	if (rd->type == TK_REDIR_OUT)
		fd = open(rd->file,  O_WRONLY |  O_TRUNC | O_CREAT, 0777);
	else
		fd = open(rd->file,  O_WRONLY |  O_APPEND | O_CREAT, 0777);
	return (fd);// to close after
}

int	execute_cmd(t_cmd *cmd)
{
	int		pid;
	char	*path;

	path = ft_strdup("/bin/");
	if (cmd->args != NULL && cmd->args[0] != NULL)
		path = ft_strjoin(path, cmd->args[0]);
	else
	{
		free(path);
		//handle redir;
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		dup2(fd_stdin(cmd), STDIN_FILENO);
		dup2(fd_stdout(cmd), STDOUT_FILENO);
		execve(path, cmd->args, NULL);
	}
	free(path);
	wait(NULL);
	return (0);
}
