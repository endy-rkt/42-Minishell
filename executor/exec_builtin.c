/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:23:16 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/19 12:57:08 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_builtin(t_cmd *cmd)
{
	char	**argv;

	if (cmd == NULL)
		return (0);
	argv = cmd->args;
	if (argv == NULL || argv[0] == NULL)
		return (0);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "env") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "export") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (1);
	return (0);
}

int	exec_piped_builtin(t_ast *ast, char **my_envp, t_sh_params **shell_params)
{
	t_cmd	*cmd;
	t_list	*lst_redir;
	int		status;

	cmd = ast->cmd;
	lst_redir = cmd->redir;
	if (change_redir(lst_redir, STDIN_FILENO, STDOUT_FILENO))
		status = buildin(cmd->args, &my_envp, STDOUT_FILENO);
	clear_and_close(shell_params);
	exit(status);
}
