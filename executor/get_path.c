/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:19:00 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/03 15:03:21 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	empty_cmd(char **args, int *err_status)
{
	if (args == NULL || args[0] == NULL)
		return (1);
	if (args[0][0] == '\0')
	{
		*err_status = 127;
		print_exec_error(args[0], "Command not found\n");
		return (1);
	}
	if (ft_strcmp(args[0], ".") == 0)
	{
		*err_status = 2;
		print_exec_error(args[0], "filename argument required\n");
		return (1);
	}
	if (ft_strcmp(args[0], "..") == 0)
	{
		*err_status = 127;
		print_exec_error(args[0], "Command not found\n");
		return (1);
	}
	return (0);
}

int	existing_directory(char **args, int *err_status)
{
	struct stat	statbuf;

	if (lstat(args[0], &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		if (ft_strchr(args[0], '/'))
		{
			*err_status = 126;
			print_exec_error(args[0], "Is a directory\n");
		}
		return (1);
	}
	return (0);
}

int	executable_file(char **args, int *err_status)
{
	int			access_code;
	struct stat	sb;

	access_code = not_valid_path(args[0]);
	if (lstat(args[0], &sb) == 0 && S_ISREG(sb.st_mode))
	{
		if (!ft_strchr(args[0], '/'))
			return (0);
		if (access_code == 126)
		{
			*err_status = 126;
			print_exec_error(args[0], "Permission denied\n");
		}
		return (1);
	}
	if (ft_strchr(args[0], '/') && access_code == 127)
	{
		*err_status = 127;
		print_exec_error(args[0], "No such file or directory\n");
		return (1);
	}
	return (0);
}

char	*get_path(char **args, char **my_envp, int *err_status)
{
	char	*path;

	path = NULL;
	if (empty_cmd(args, err_status))
		return (NULL);
	if (existing_directory(args, err_status) || executable_file(args,
			err_status))
		return (ft_strdup(args[0]));
	path = path_from_env(args, my_envp, err_status);
	return (path);
}
