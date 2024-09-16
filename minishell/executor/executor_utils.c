/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:12:03 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/16 15:20:40 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*execute_cmd(shell_params); **
execute_pipeline(shell_params);*/

/*
waitpid(pid, &path_error, 0) == -1;
	if (WIFEXITED(path_error))
	    path_error = WEXITpath_error(path_error);
    else if (WIFSIGNALED(path_error))
	    path_error = WEXITSTATUS(path_error);*/
int	change_redir(t_list *lst_redir, int stdin, int stdout)
{
	int	*fd;

	fd = redir_value(lst_redir);
	if (fd[0] == -1 || fd[1] == -1)
		return (0);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	dup2(fd[0], stdin);
	dup2(fd[1], stdout);
	free(fd);
	return (1);
}

int	exec_cmd(char **args, t_list *lst_redir, char **my_envp)
{
	int		status;
	int		pid;
	char	*path;

	path = get_path(args, my_envp, &status);
	if (status != 0)
	{
		free(path);
		return (status);
	}
	pid = fork();
	if (pid == 0)
	{
		if (change_redir(lst_redir, STDIN_FILENO, STDOUT_FILENO))
			execve(path, args, my_envp);
		free(path);
		ft_lstclear(&lst_redir, NULL);//to call method
		exit(1);
	}
	free(path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	    status = WIFEXITED(status);
    else if (WIFSIGNALED(status))
	    status = WEXITSTATUS(status);
	return (status);
}

void	spwan_child(t_ast *ast, char **my_envp, int fd_0, int fd_1)
{
	t_cmd	*cmd;
	t_list	*lst_redir;
	int		status;
	char	*path;

	cmd = ast->cmd;
	path = get_path(cmd->args, my_envp, &status);
	if (status != 0)
	{
		free(path);
		exit(status);
	}
	if (change_redir(lst_redir, fd_0, fd_1))
		execve(path, cmd->args, my_envp);
	free(path);
	// free();
	exit(1);
}

void	exec_node(t_ast *ast_node, char **my_envp, int fd_0, int fd_1)
{
	if (ast_node)
	{
		if (ast_node->node_type == NODE_CMD)
			launch_child(ast_node, my_envp, fd_0, fd_1);
		else
			exec_pipeline(ast_node, my_envp);
	}
}

int	get_status(int pid_0, int pid_1)
{
	int status;

	status = 0;
	waitpid(pid_0, &status, 0);
	waitpid(pid_1, &status, 0);
	if (WIFEXITED(status))
	    status = WIFEXITED(status);
    else if (WIFSIGNALED(status))
	    status = WEXITSTATUS(status);
	return (status);
}

int	exec_pipeline(t_ast *ast, char **my_envp)
{
	int	fd[2];
	int	pid[2];
	int	status;

	pipe(fd);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(fd[0]);
		exec_node(ast->left_node, my_envp, fd[0], fd[1]);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		close(fd[1]);
		exec_node(ast->right_node, my_envp, fd[0], fd[1]);
	}
	close(fd[0]);
	close(fd[1]);
	status = get_status(pid[0], pid[1]);
	return (status);
}

void	execute_cmd(t_sh_params **shell_params)
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

void	execute_pipeline(t_sh_params **shell_params)
{
	t_ast	*ast;
	char	**my_envp;
	int		exit_status;

	exit_status = 0;
	ast = (*shell_params)->ast;
	my_envp = (*shell_params)->my_envp;
	exit_status = exec_pipeline(ast, my_envp);
	(*shell_params)->exit_status = exit_status;
}
