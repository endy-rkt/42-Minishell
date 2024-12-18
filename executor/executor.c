/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:06:43 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/03 14:18:21 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	exec_void_cmd(t_ast *ast, t_sh_params **shell_params)
{
	int		*fd;
	t_cmd	*cmd;

	if (ast->cmd == NULL)
		return (0);
	cmd = ast->cmd;
	if (cmd->args == NULL || cmd->args[0] == NULL)
	{
		(*shell_params)->exit_status = 1;
		if (cmd->redir == NULL)
			return (1);
		else
		{
			fd = redir_value(cmd->redir);
			if (fd[0] != -1 && fd[1] != -1)
				(*shell_params)->exit_status = 0;
			free(fd);
			return (1);
		}
	}
	(*shell_params)->exit_status = 0;
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
	status = buildin(cmd->args, shell_params, fd);
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
	int		exit_status;

	exit_status = 0;
	ast = (*shell_params)->ast;
	cmd = ast->cmd;
	exit_status = exec_cmd(cmd->args, cmd->redir, shell_params);
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
	if (exit_status == 130 || exit_status == 131)
		ft_printf("\n");
	(*shell_params)->exit_status = exit_status;
}

void	execute(t_sh_params **shell_params)
{
	t_ast	*ast;

	ast = (*shell_params)->ast;
	if (ast == NULL)
		return ;
	if (ast->t_node_type == NODE_CMD)
	{
		if (exec_void_cmd(ast, shell_params))
			return ;
		if (is_builtin(ast->cmd))
			(*shell_params)->exit_status = exec_builtin(shell_params);
		else
			execute_cmd(shell_params);
	}
	else
		execute_pipeline(shell_params);
}
