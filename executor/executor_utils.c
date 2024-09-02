/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:01:49 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/02 16:20:24 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	free_ast(t_ast **ast)
{
	
}

int	fd_stdin(t_cmd *cmd)
{
	int		fd;
	t_list	*redir_in;
	t_list	*last_redir;
	t_redir *rd;

	redir_in = cmd->redir_in;
	if (redir_in == NULL)
		return (STDIN_FILENO);
	last_redir = ft_lstlast(redir_in);
	rd = last_redir->content;
	fd = open(rd->file, O_RDONLY);
	printf("fd==%d\n",fd);
	//create file;
	return (fd);
}

int	fd_stdout(t_cmd *cmd)
{
	int		fd;
	t_list	*redir_out;
	t_list	*last_redir;
	t_redir *rd;

	redir_out = cmd->redir_out;
	if (redir_out == NULL)
		return (STDOUT_FILENO);
	last_redir = ft_lstlast(redir_out);
	rd = last_redir->content;
	fd = open(rd->file,  O_WRONLY| O_TRUNC | O_CREAT, 0777);
	//create file;
	printf("fd==%d\n",fd);
	return (fd);
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
		//dup2(fd_stdin(cmd), STDIN_FILENO);
		dup2(fd_stdout(cmd), STDOUT_FILENO);
		execve(path, cmd->args, NULL);
	}
	free(path);
	wait(NULL);
	return (0);
}
