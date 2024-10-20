/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:19:08 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/20 07:00:47 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	child_cmd(char **args, t_list *lst_redir, t_sh_params **shell_params)
{
	int		status;
	char	*path;

	status = 0;
	path = NULL;
	if (change_redir(lst_redir, STDIN_FILENO, STDOUT_FILENO))
	{
		path = get_path(args, (*shell_params)->my_envp, &status);
		if (status == 0)
			execve(path, args, (*shell_params)->my_envp);
	}
	if (path)
		free(path);
	clear_and_close(shell_params);
	if (status == 0)
		exit(EXIT_FAILURE);
	else
		exit(status);
}

int	exec_cmd(char **args, t_list *lst_redir, t_sh_params **shell_params)
{
	int		status;
	int		pid;

	pid = fork();
	signal(SIGINT, child_sigint_handler);
	if (pid == 0)
		child_cmd(args, lst_redir, shell_params);
	status = get_status(pid);
	return (status);
}