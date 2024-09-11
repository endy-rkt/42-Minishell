/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:01:49 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 17:14:55 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	free_ast(t_ast **ast)
{
	
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
		if (rd->type == TK_REDIR_IN2)
		{
			fd = open(rd->file,  O_RDWR | O_CREAT, 0777);
			close(fd);
		}
		else if (rd->type == TK_REDIR_IN)
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

int	execute_cmd(t_ast *ast, char **my_envp, int fd_0, int fd_1)
{
	int		pid;
	char	*path;
	t_cmd	*cmd;

	cmd = ast->cmd;
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
		 signal(SIGINT, SIG_DFL);
		dup2(fd_0, STDIN_FILENO);
		dup2(fd_1, STDOUT_FILENO);
		dup2(fd_stdin(cmd), STDIN_FILENO);
		dup2(fd_stdout(cmd), STDOUT_FILENO);
		execve(path, cmd->args, NULL);
	}
	// printf("path=%s\n",path);
	free(path);
	return (0);
}

void	no_pipe_cmd(t_ast *ast, int fd_0, int fd_1)
{
	char	*path;
	t_cmd	*cmd;

	cmd = ast->cmd;
	path = ft_strdup("/bin/");
	if (cmd->args != NULL && cmd->args[0] != NULL)
		path = ft_strjoin(path, cmd->args[0]);
	else
	{
		free(path);
		//handle redir;
		exit(EXIT_FAILURE);
	}
	dup2(fd_0, STDIN_FILENO);
	dup2(fd_1, STDOUT_FILENO);
	dup2(fd_stdin(cmd), STDIN_FILENO);
	dup2(fd_stdout(cmd), STDOUT_FILENO);
	execve(path, cmd->args, NULL);
}


int execute_pipe(t_ast *ast, char **my_envp)
{
    int fd[2];
    int pid1, pid2;

    // Create a pipe
    if (pipe(fd) < 0)
    {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    // Fork the first process
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) 
    {
        // Child process for the left command
		 signal(SIGINT, SIG_DFL);
        close(fd[0]);  // Close unused read end
        if (dup2(fd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2 failed");
            exit(EXIT_FAILURE);
        }
        close(fd[1]);  // Close after duplication
        
        if (ast->left_node)
        {
            if (ast->left_node->node_type == NODE_CMD && ast->left_node->cmd != NULL)
                no_pipe_cmd(ast->left_node, STDIN_FILENO, STDOUT_FILENO);
            else
                execute_pipe(ast->left_node, my_envp);
        }
        exit(EXIT_SUCCESS);
    }

    // Fork the second process
    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0)
    {
        // Child process for the right command
		signal(SIGINT, SIG_DFL);
        close(fd[1]);  // Close unused write end
        if (dup2(fd[0], STDIN_FILENO) == -1)
        {
            perror("dup2 failed");
            exit(EXIT_FAILURE);
        }
        close(fd[0]);  // Close after duplication

        if (ast->right_node)
        {
            if (ast->right_node->node_type == NODE_CMD && ast->right_node->cmd != NULL)
                no_pipe_cmd(ast->right_node, STDIN_FILENO, STDOUT_FILENO);
            else
                execute_pipe(ast->right_node, my_envp);
        }
        exit(EXIT_SUCCESS);
    }

    // Close parent’s pipe ends
    close(fd[0]);
    close(fd[1]);

    // Wait for both child processes
    if (waitpid(pid1, NULL, 0) == -1)
    {
        perror("waitpid failed for pid1");
        exit(EXIT_FAILURE);
    }

    if (waitpid(pid2, NULL, 0) == -1)
    {
        perror("waitpid failed for pid2");
        exit(EXIT_FAILURE);
    }

    return 0;
}


