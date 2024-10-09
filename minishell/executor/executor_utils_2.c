/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:58:21 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/09 15:19:04 by trazanad         ###   ########.fr       */
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


char	*get_path(char **args, char **my_envp, int *err_status)
{
	int		i;
	char	*path;
	char	**tmp;

	i = 0;
	if (!not_valid_path(args[0]))
		return (ft_strdup(args[0]));
	while (ft_strnstr(my_envp[i], "PATH=", 5) == 0)
		i++;
	tmp = ft_split(my_envp[i] + 5, ':');
	i = 0;
	while (tmp[i] != NULL)
	{
		path = ft_strjoin(tmp[i], "/");
		path = ft_strjoin(path, args[0]);
		*err_status = not_valid_path(path);
		if (!*err_status) 
			break ;
		free(path);
		path = NULL;
		i++;
	}
	if (path == NULL)
		ft_putstr_fd("Command not found\n", 2);
	// free_args(tmp);
	return (path);
}
