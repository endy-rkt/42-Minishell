/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:12:03 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/16 13:49:54 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	change_redir(t_list *lst_redir, int stdin, int stdout)
{
	int	*fd;

	fd = redir_value(lst_redir);
	if (fd[0] == -1 || fd[1] == -1)
		return (0);
	if (fd[0] != STDIN_FILENO)
        dup2(fd[0], STDIN_FILENO);
    if (fd[1] != STDOUT_FILENO)
        dup2(fd[1], STDOUT_FILENO);
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
	    status = WTERMSIG(status) + 18;
	// ft_printf("\033[2K\r");
	return (status);
}

void	launch_child(t_ast *ast, char **my_envp, t_sh_params **shell_params)
{
	t_cmd	*cmd;
	t_list	*lst_redir;
	int		status;
	char	*path;

	cmd = ast->cmd;
	lst_redir = cmd->redir;
	path = get_path(cmd->args, my_envp, &status);
	if (status != 0)
	{
		if (path)
			free(path);
		cmd_clear(&((*shell_params)->cmd));
		if (*shell_params)
			free_sh_params(shell_params);
		exit(status);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (change_redir(lst_redir, STDIN_FILENO, STDOUT_FILENO))
		execve(path, cmd->args, my_envp);
	free(path);
	cmd_clear(&((*shell_params)->cmd));
	if (*shell_params)
		free_sh_params(shell_params);
	exit(1);
}

int	piped_builtin(t_ast *ast, char **my_envp, t_sh_params **shell_params)
{
	t_cmd	*cmd;
	t_list	*lst_redir;
	int		status;

	cmd = ast->cmd;
	lst_redir = cmd->redir;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (change_redir(lst_redir, STDIN_FILENO, STDOUT_FILENO))
		status = buildin(cmd->args, &my_envp, STDOUT_FILENO);
	// free_args(my_envp);
	// ast_clear(&ast);
	cmd_clear(&((*shell_params)->cmd));
		if (*shell_params)
			free_sh_params(shell_params);
	exit(1);
}

void	exec_node(t_ast *ast_node, char **my_envp, t_sh_params **shell_params)
{
	if (ast_node)
	{
		if (ast_node->node_type == NODE_CMD)
		{
			if (is_builtin(ast_node->cmd))
				piped_builtin(ast_node, my_envp, shell_params);
			else
				launch_child(ast_node, my_envp, shell_params);
		}
		else
			exec_pipeline(ast_node, my_envp, shell_params);
	}
}


