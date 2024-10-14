/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:06:43 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/11 16:59:15 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	cmd_child(char **args, t_list *lst_redir, char *path, char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (change_redir(lst_redir, STDIN_FILENO, STDOUT_FILENO))
		execve(path, args, envp);
	free(path);
	free_args(args);
	// free_args(my_envp);
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

int exec_pipeline(t_ast *ast, char **my_envp)
{
	int	fd[2];
	int	pid[2];

	pipe(fd);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);  
        close(fd[1]); 
		exec_node(ast->left_node, my_envp, STDIN_FILENO, STDOUT_FILENO);
		exit(EXIT_FAILURE); 
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]); 
		exec_node(ast->right_node, my_envp, STDOUT_FILENO, STDOUT_FILENO);
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

static void	execute_pipeline(t_sh_params **shell_params)
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

void	execute(t_sh_params **shell_params)
{
	t_ast	*ast;

	ast = (*shell_params)->ast;
	if (ast == NULL)
		return ;
	if (ast->node_type == NODE_CMD)
		execute_cmd(shell_params);
	else
		execute_pipeline(shell_params);
}