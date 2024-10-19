/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:06:43 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/19 14:19:56 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	exec_void_cmd(t_ast *ast)
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
	{
		free(fd);
		return (1);
	}
	status = buildin(cmd->args, &((*shell_params)->my_envp), fd[1]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	free(fd);
	return (status);
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
	exit_status = exec_cmd(cmd->args, cmd->redir,shell_params);
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
	exit_status = exec_pipeline(ast, my_envp, shell_params);
	(*shell_params)->exit_status = exit_status;
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
		if (exec_void_cmd(ast))
			return ;
		if (is_builtin(ast->cmd))
			exec_builtin(shell_params);
		else
			execute_cmd(shell_params);
	}
	else
		execute_pipeline(shell_params);
}
