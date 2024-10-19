/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:12:03 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/19 13:25:33 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	get_status(int pid)
{
	int status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	    status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	return (status);
}

static void	launch_child(t_ast *ast, char **my_envp, t_sh_params **shell_params)
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
		clear_and_close(shell_params);
		exit(status);
	}
	if (change_redir(lst_redir, STDIN_FILENO, STDOUT_FILENO) && cmd->args[0] != NULL)
		execve(path, cmd->args, my_envp);
	free(path);
	status = (*shell_params)->exit_status;
	clear_and_close(shell_params);
	exit(status);
}

void	exec_node(t_ast *ast_node, char **my_envp, t_sh_params **shell_params)
{
	if (ast_node)
	{
		if (ast_node->node_type == NODE_CMD)
		{
			if (exec_void_cmd(ast_node))
			{
				cmd_clear(&((*shell_params)->cmd));
				free_args((*shell_params)->my_envp);
				free_sh_params(shell_params);
				exit(0);
			}
			if (is_builtin(ast_node->cmd))
				exec_piped_builtin(ast_node, my_envp, shell_params);
			else
				launch_child(ast_node, my_envp, shell_params);
		}
		else
			exec_pipeline(ast_node, my_envp, shell_params);
	}
}


