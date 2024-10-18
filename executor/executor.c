/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:06:43 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/18 09:23:37 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	sigint_handler(int sig)
{
    (void)sig;
	// ft_printf("\n");
}

static int	cmd_child(char **args, t_list *lst_redir, char *path, char **envp)
{
	if (change_redir(lst_redir, STDIN_FILENO, STDOUT_FILENO))
		execve(path, args, envp);
	free(path);
	free_args(args);
	free_args(envp);
	ft_lstclear(&lst_redir, free_redir);
	exit(1);
}

static int	exec_cmd(char **args, t_list *lst_redir, char **my_envp)
{
	int		status;
	int		pid;
	char	*path;

	status = 0;
	path = get_path(args, my_envp, &status);
	if (status != 0)
	{
		if (path)
			free(path);
		return (status);
	}
	pid = fork();
	signal(SIGINT, sigint_handler);
	if (pid == 0)
		cmd_child(args, lst_redir, path, my_envp);
	free(path);
	status = get_status(pid);
	return (status);
}

int	pipe_status(int fd_0, int fd_1, int pid_0, int pid_1)
{
	int	status;

	status = 0;
	close(fd_0);
	close(fd_1);
	waitpid(pid_0, &status, 0);
	status = get_status(pid_1);
	return (status);
}

void	free_params(t_sh_params **shell_params)
{
	free_args((*shell_params)->my_envp);
	cmd_clear(&((*shell_params)->cmd));
	if (*shell_params)
		free_sh_params(shell_params);
}

void	update_fileno(int to_close_fd, int to_dup_fd, int fd)
{
	close(to_close_fd);
	dup2(to_dup_fd, fd);
	close(to_dup_fd);
}

int exec_pipeline(t_ast *ast, char **my_envp, t_sh_params **shell_params)
{
	int	fd[2];
	int	pid[2];

	pipe(fd);
	pid[0] = fork();
	signal(SIGINT, sigint_handler);
	if (pid[0] == 0)
	{
		update_fileno(fd[0], fd[1], STDOUT_FILENO);
		exec_node(ast->left_node, my_envp, shell_params);
		free_params(shell_params);
		exit(EXIT_FAILURE); 
	}
	pid[1] = fork();
	signal(SIGINT, sigint_handler);
	if (pid[1] == 0)
	{
		update_fileno(fd[1], fd[0], STDIN_FILENO);
		exec_node(ast->right_node, my_envp, shell_params);
		free_params(shell_params);
		exit(EXIT_FAILURE); 
	}
	return (pipe_status(fd[0], fd[1], pid[0], pid[1]));
}

static void	execute_cmd(t_sh_params **shell_params)
{
	t_ast	*ast;
	t_cmd	*cmd;
	char	**my_envp;
	int		exit_status;

	exit_status = 0;
	ast = (*shell_params)->ast;
	my_envp = (*shell_params)->my_envp;
	cmd = ast->cmd;
	exit_status = exec_cmd(cmd->args, cmd->redir, my_envp);
	(*shell_params)->exit_status = exit_status;
}

int	exec_builtin(t_sh_params **shell_params)
{
	int		*fd;
	int		status;
	t_cmd	*cmd;
	t_ast	*ast;

	ast = (*shell_params)->ast;
	if (ast == NULL)
		return (1);
	cmd = ast->cmd;
	if (cmd == NULL)
		return (1);
	status = 0;
	fd = redir_value(cmd->redir);
	if (fd[0] == -1 || fd[1] == -1)
		return (1);
	status = buildin(cmd->args, &((*shell_params)->my_envp), fd[1]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	free(fd);
	return (status);
}

static void	execute_pipeline(t_sh_params **shell_params)
{
	t_ast	*ast;
	char	**my_envp;
	int		exit_status;

	exit_status = 0;
	ast = (*shell_params)->ast;
	my_envp = (*shell_params)->my_envp;
	exit_status = exec_pipeline(ast, my_envp, shell_params);
	(*shell_params)->exit_status = exit_status;
}

int	check_command(t_ast *ast)
{
	int		*fd;
	t_cmd	*cmd;
	t_list	*redir;

	if (ast->cmd == NULL)
		return (1);
	cmd = ast->cmd;
	if (cmd->args == NULL || cmd->args[0] == NULL)
	{
		if (cmd->redir == NULL)
			return (1);
		else
		{
			fd = redir_value(cmd->redir);
			free(fd);
			return (1);
		}
	}
	return (0);
}

void	execute(t_sh_params **shell_params)
{
	t_ast	*ast;
	char	**args;

	ast = (*shell_params)->ast;
	if (ast == NULL)
		return ;
	if (ast->node_type == NODE_CMD)
	{
		if (check_command(ast))
			return ;
		if (is_builtin(ast->cmd))
			exec_builtin(shell_params);
		else
			execute_cmd(shell_params);
	}
	else
		execute_pipeline(shell_params);
}
