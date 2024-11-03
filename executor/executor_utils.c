/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:54:27 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/03 15:53:44 by trazanad         ###   ########.fr       */
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
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (0);
		close(fd[0]);
	}
	if (fd[1] != STDOUT_FILENO)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (0);
		close(fd[1]);
	}
	free(fd);
	return (1);
}

void	print_exec_error(char *arg_name, char *message)
{
	char	*str;

	str = ft_strdup(arg_name);
	str = ft_strjoin(str, ": ");
	str = ft_strjoin(str, message);
	ft_putstr_fd(str, 2);
	free(str);
}

int	not_valid_path(char *path)
{
	if (access(path, F_OK) != 0)
		return (127);
	if (access(path, X_OK) != 0)
		return (126);
	return (0);
}

void	child_sigint_handler(int sig)
{
	(void)sig;
}
