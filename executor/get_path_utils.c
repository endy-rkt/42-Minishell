/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:02:30 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/03 15:04:24 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	**path_exist(char **my_envp, int *err_status)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	while (my_envp[i])
	{
		if (export_match(my_envp[i], "PATH") && my_envp[i][4] == '=')
		{
			tmp = ft_split(my_envp[i] + 5, ':');
			return (tmp);
		}
		i++;
	}
	*err_status = 127;
	return (NULL);
}

static char	*path_is_unset(char **args, int *err_status)
{
	int			access_code;
	char		*path;
	struct stat	sb;

	access_code = not_valid_path(args[0]);
	if (lstat(args[0], &sb) == 0 && S_ISREG(sb.st_mode))
	{
		path = ft_strdup(args[0]);
		*err_status = access_code;
		if (access_code == 126)
			print_exec_error(args[0], "Permission denied\n");
		return (path);
	}
	print_exec_error(args[0], "No such file or directory\n");
	return (NULL);
}

char	*path_from_env(char **args, char **my_envp, int *err_status)
{
	int		i;
	char	*path;
	char	*tmp_path;
	char	**tmp;

	tmp = path_exist(my_envp, err_status);
	if (!tmp)
		return (path_is_unset(args, err_status));
	i = 0;
	while (tmp[i] != NULL)
	{
		tmp_path = ft_strdup(tmp[i]);
		path = ft_strjoin(tmp_path, "/");
		path = ft_strjoin(path, args[0]);
		*err_status = not_valid_path(path);
		if (*err_status == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	free_args(tmp);
	if (path == NULL)
		print_exec_error(args[0], "Command not found\n");
	return (path);
}
