/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:43:23 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/04 09:29:15 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

static void	update_env(char *key, char *value, char ***env)
{
	char	*val;
	char	**args;

	args = malloc(sizeof(char *) * 3);
	if (!args)
		return ;
	val = ft_strdup(key);
	val = ft_strjoin(val, "=");
	val = ft_strjoin(val, value);
	args[0] = ft_strdup("export");
	args[1] = val;
	args[2] = NULL;
	ft_export(args, env, 1);
	free_args(args);
}

int	navigate_to_path(char *path, char ***env)
{
	char	current_dir[4096];

	if (chdir(path))
	{
		perror("cd");
		return (1);
	}
	getcwd(current_dir, sizeof(current_dir));
	update_env("PWD", current_dir, env);
	return (0);
}

int	navigate_to_home(char ***env)
{
	char	*home_path;

	home_path = get_env_value("HOME", *env);
	if (home_path == NULL)
	{
		ft_putstr_fd("cd : Home not set\n", 2);
		return (1);
	}
	return (navigate_to_path(home_path, env));
}

int	navigate_to_oldpwd(char ***env)
{
	char	*oldpwd;

	oldpwd = get_env_value("OLDPWD", *env);
	if (oldpwd == NULL)
	{
		ft_putstr_fd("cd : OLDPWD not set\n", 2);
		return (1);
	}
	return (navigate_to_path(oldpwd, env));
}

int	ft_cd(char **argv, char ***env, t_sh_params *shell_params)
{
	int			status;
	char		start_dir[4096];
	char		*tmp;

	status = 0;
	tmp = ft_strdup(my_getenv("PWD", shell_params));
	getcwd(start_dir, sizeof(start_dir));
	if (argv[1] == NULL)
		status = navigate_to_home(env);
	else if (argv[1] != NULL && argv[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else if (ft_strcmp(argv[1], "-") == 0)
		status = navigate_to_oldpwd(env);
	else
		status = navigate_to_path(argv[1], env);
	if (status == 0)
	{
		update_env("OLDPWD", tmp, env);
		free(tmp);
	}
	return (status);
}
