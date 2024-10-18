/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 08:54:48 by ferafano          #+#    #+#             */
/*   Updated: 2024/10/18 08:20:17 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int	is_match(char *line_read, char **copy_env)
{
	int	i;
	int	j;
	int	success;

	success = 0;
	i = 0;
	while (copy_env[i])
	{
		if (copy_env[i][0] == line_read[0])
		{
			j = 1;
			success = 1;
			while (line_read[j])
			{
				if (copy_env[i][j] != line_read[j])
					break ;
				j++;
			}
			if (success)
				return (i);
		}
		i++;
	}
	return (-1);
}

int	change_to_home(char *cwd, char **copy_env, char *home)
{
	update_oldpwd("OLDPWD", cwd, copy_env);
	if (chdir(home))
	{
		write(2, "cd : Home not set\n", 18);
		return (1);
	}
	return (0);
}

int	change_to_oldpwd(char *cwd, char **copy_env)
{
	if (chdir(search_envp("OLDPWD", copy_env)) == 0)
	{
		update_oldpwd("OLDPWD", cwd, copy_env);
		return (0);
	}
	else
	{
		perror("OLDPWD not set");
		return (1);
	}
}

int	get_prefix_length(char *line_read)
{
	int	len;

	len = 0;
	while (line_read[len] && line_read[len] != '=')
		len++;
	return (len);
}

char	*search_envp(char *line_read, char **copy_env)
{
	int	len;
	int	is_index;

	len = get_prefix_length(line_read);
	is_index = is_match(line_read, copy_env);
	if (is_index == -1)
		return (NULL);
	return (copy_env[is_index] + len + 1);
}
