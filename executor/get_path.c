/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:58:21 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/29 18:38:42 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	empty_cmd(char **args, int *err_status)
{
	if (args[0] == NULL)
		return (1);
	if (args[0][0] == '\0')
	{
		*err_status = 127;
		print_exec_error(args[0], "Command not found\n");
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
			break ;
		free(path);
		path = NULL;
		i++;
	}
	if (path == NULL)
		print_exec_error(args[0], "Command not found\n");
	return (path);
}

static int	only_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '/' && str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}

static int	check_local_path(char **args, int *err_status)
{
	int	access_code;

	access_code = not_valid_path(args[0]);
	if (only_slash(args[0]))
	{
		if (access_code == 0)
		{
			*err_status = 126;
			print_exec_error(args[0], "Is a directory\n");
		}
		else
		{
			*err_status = access_code;
			print_exec_error(args[0], "No such file or directory\n");
		}
		return (1);
	}
	if (access_code == 126 && (args[0][0] == '.' && args[0][1] == '/'))
	{
		*err_status = access_code;
		print_exec_error(args[0], "Permission denied\n");
		return (1);
	}
	return (0);
}

static int	path_not_set(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (0);
		i++;
	}
	ft_printf("minishell: path not set");
	return (1);
}

char	*get_path(char **args, char **my_envp, int *err_status)
{
	int		i;
	char	*path;
	char	**tmp;

	path = NULL;
	if (empty_cmd(args, err_status) || check_local_path(args, err_status))
		return (NULL);
	if (!not_valid_path(args[0]))
		return (ft_strdup(args[0]));
	if (path_not_set(my_envp))
		return (NULL);
	i = 0;
	while (my_envp[i] != NULL && ft_strnstr(my_envp[i], "PATH=", 5) == 0)
		i++;
	if (my_envp[i] == NULL)
	{
		print_exec_error(args[0], "Command not found\n");
		return (NULL);
	}
	tmp = ft_split(my_envp[i] + 5, ':');
	path = path_from_env(args, tmp, err_status);
	free_args(tmp);
	return (path);
}
