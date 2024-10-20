/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:20:45 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/21 11:11:34 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	clear_and_close(t_sh_params **shell_params)
{
	free_args((*shell_params)->my_envp);
	cmd_clear(&((*shell_params)->cmd));
	if (*shell_params)
		free_sh_params(shell_params);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

static	int pipe_status(int fd_0, int fd_1, int pid_0, int pid_1)
{
	int	status;

	status = 0;
	close(fd_0);
	close(fd_1);
	waitpid(pid_0, &status, 0);
	status = get_status(pid_1);
	return (status);
}

static	void update_fileno(int to_close_fd, int to_dup_fd, int fd)
{
	close(to_close_fd);
	dup2(to_dup_fd, fd);
	close(to_dup_fd);
}

int exec_pipeline(t_ast *ast, char **my_envp, t_sh_params **shell_params)
{
	int	fd[2];
	int	pid[2];

	pipe(fd);
	pid[0] = fork();
	signal(SIGINT, child_sigint_handler);
	if (pid[0] == 0)
	{
		update_fileno(fd[0], fd[1], STDOUT_FILENO);
		exec_node(ast->left_node, my_envp, shell_params);
		clear_and_close(shell_params);
		exit(EXIT_FAILURE); 
	}
	pid[1] = fork();
	signal(SIGINT, child_sigint_handler);
	if (pid[1] == 0)
	{
		update_fileno(fd[1], fd[0], STDIN_FILENO);
		exec_node(ast->right_node, my_envp, shell_params);
		clear_and_close(shell_params);
		exit(EXIT_FAILURE); 
	}
	return (pipe_status(fd[0], fd[1], pid[0], pid[1]));
}
