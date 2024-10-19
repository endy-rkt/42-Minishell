/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:19:08 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/19 13:55:20 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	child_cmd(char **args, t_list *lst_redir, char *path, t_sh_params **shell_params)
{
	if (change_redir(lst_redir, STDIN_FILENO, STDOUT_FILENO))
		execve(path, args, (*shell_params)->my_envp);
	free(path);
	clear_and_close(shell_params);
	exit(1);
}

int	exec_cmd(char **args, t_list *lst_redir, t_sh_params **shell_params)
{
	int		status;
	int		pid;
	char	*path;

	status = 0;
	path = get_path(args, (*shell_params)->my_envp, &status);
	if (status != 0)
	{
		if (path)
			free(path);
		return (status);
	}
	pid = fork();
	signal(SIGINT, child_sigint_handler);
	if (pid == 0)
		child_cmd(args, lst_redir, path, shell_params);
	free(path);
	status = get_status(pid);
	return (status);
}
