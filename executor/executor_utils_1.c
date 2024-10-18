/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:12:03 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/18 13:34:04 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	change_redir(t_list *lst_redir, int stdin, int stdout)
{
	int	*fd;

	fd = redir_value(lst_redir);
	if (fd[0] == -1 || fd[1] == -1)
	{
		free(fd);
		return (0);
	}
	if (fd[0] != STDIN_FILENO)
	{
        dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
    if (fd[1] != STDOUT_FILENO)
    {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	free(fd);
	return (1);
}

int	get_status(int pid)
{
	int status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	    status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
	    status = WTERMSIG(status);
	return (status);
}

void	launch_child(t_ast *ast, char **my_envp, t_sh_params **shell_params)
{
	t_cmd	*cmd;
	t_list	*lst_redir;
	int		status;
	char	*path;

	cmd = ast->cmd;
	status = 0;
	lst_redir = cmd->redir;
	path = get_path(cmd->args, my_envp, &status);
	if (status != 0)
	{
		if (path)
			free(path);
		free_params(shell_params);
		exit(status);
	}
	if (change_redir(lst_redir, STDIN_FILENO, STDOUT_FILENO) && cmd->args[0] != NULL)
		execve(path, cmd->args, my_envp);
	free(path);
	free_params(shell_params);
	exit(1);
}

int	piped_builtin(t_ast *ast, char **my_envp, t_sh_params **shell_params)
{
	t_cmd	*cmd;
	t_list	*lst_redir;
	int		status;

	cmd = ast->cmd;
	lst_redir = cmd->redir;
	if (change_redir(lst_redir, STDIN_FILENO, STDOUT_FILENO))
		status = buildin(cmd->args, &my_envp, STDOUT_FILENO);
	free_params(shell_params);
	exit(1);
}

int	empty_command(t_ast *ast, t_sh_params **shell_params)
{
	if (check_command(ast))
	{
		free_params(shell_params);
		return (1);
	}
	return (0);
}

void	exec_node(t_ast *ast_node, char **my_envp, t_sh_params **shell_params)
{
	if (ast_node)
	{
		if (ast_node->node_type == NODE_CMD)
		{
			if (check_command(ast_node))
			{
				cmd_clear(&((*shell_params)->cmd));
				free_args((*shell_params)->my_envp);
				free_sh_params(shell_params);
				exit(0);
			}
			if (is_builtin(ast_node->cmd))
				piped_builtin(ast_node, my_envp, shell_params);
			else
				launch_child(ast_node, my_envp, shell_params);
		}
		else
			exec_pipeline(ast_node, my_envp, shell_params);
	}
}


