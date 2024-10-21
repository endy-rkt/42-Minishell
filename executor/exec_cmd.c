/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:19:08 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/21 12:08:18 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	child_cmd(char **args, t_list *lst_redir, t_sh_params **shell_params)
{
	int		status;
	char	*path;

	status = 0;
	path = NULL;
	signal(SIGQUIT, SIG_DFL);
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

static void	sig_handler(int sig)
{
	(void)sig;
	ft_printf("\n");
}

static int	child_status(int pid)
{
	int status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	    status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status) + 128;
		if (status == 131)
			ft_putstr_fd("\n", 2);
	}
	return (status);
}

int	exec_cmd(char **args, t_list *lst_redir, t_sh_params **shell_params)
{
	int		status;
	int		pid;

	pid = fork();
	signal(SIGINT, sig_handler);
	if (pid == 0)
		child_cmd(args, lst_redir, shell_params);
	status = child_status(pid);
	return (status);
}
