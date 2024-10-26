/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:27:11 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/25 11:31:16 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	buildin(char **argv, t_sh_params **shell_params, int *tab_fd)
{
	int		status;
	char	***copy_env;
	int		fd;

	status = 0;
	fd = tab_fd[1];
	copy_env = &((*shell_params)->my_envp);
	if (ft_strcmp(argv[0], "cd") == 0)
		// status = ft_cd(argv, *copy_env);
        status = ft_cd(argv, copy_env);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		status = ft_pwd(fd);
	else if (ft_strcmp(argv[0], "env") == 0)
		status = ft_env(*copy_env, argv, fd);
	else if (ft_strcmp(argv[0], "unset") == 0)
		status = ft_unset(argv, &*copy_env);
	else if (ft_strcmp(argv[0], "export") == 0)
		status = ft_export(argv, &*copy_env, fd);
	else if (ft_strcmp(argv[0], "echo") == 0)
		status = ft_echo(argv, fd);
	else if (ft_strcmp(argv[0], "exit") == 0)
		status = ft_exit(argv, copy_env, shell_params, tab_fd);
	return (status);
}
