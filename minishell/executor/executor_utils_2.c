/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:58:21 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/13 15:44:01 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	not_valid_path(char *path)
{
	if (access(path, F_OK) != 0)
		return (127);
	if (access(path, X_OK) != 0)
		return (126);
	return (0);
}

static int	empty_cmd(char **args, int *err_status)
{
	if (args[0] == NULL)
		return (1);
	if (args[0][0] == '\0')
	{
		*err_status = 127;
		ft_putstr_fd("Command not found\n", 2);
		return (1);
	}
	return (0);
}

static char	*path_from_env(char **args, char **tmp, int *err_status)
{
	int		i;
	char	*path;
	char	*tmp_path;

	i = 0;
	while (tmp[i] != NULL)
	{
		tmp_path = ft_strdup(tmp[i]);
		path = ft_strjoin(tmp_path, "/");
		path = ft_strjoin(path, args[0]);
		*err_status = not_valid_path(path);
		if (*err_status == 0)
			break;
		free(path);
		path = NULL;
		i++;
	}
	if (path == NULL)
		ft_putstr_fd("Command not found\n", 2);
	return (path);
}

char	*get_path(char **args, char **my_envp, int *err_status)
{
	int		i;
	char	*path;
	char	**tmp;

	if (empty_cmd(args, err_status))
		return (NULL);
	if (!not_valid_path(args[0]))
		return (ft_strdup(args[0]));
	i = 0;
	while (ft_strnstr(my_envp[i], "PATH=", 5) == 0)
		i++;
	tmp = ft_split(my_envp[i] + 5, ':');
	path = path_from_env(args, tmp, err_status);
	free_args(tmp);
	return (path);
}
