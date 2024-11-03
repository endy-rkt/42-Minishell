/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 08:53:49 by ferafano          #+#    #+#             */
/*   Updated: 2024/11/03 13:09:26 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*original_dest;

	original_dest = dest;
	while ((*dest++ = *src++) != '\0')
		;
	return (original_dest);
}

int	is_valid_flag(char *argv)
{
	int	i;
	int	ok;

	i = 1;
	ok = 0;
	while (argv[i] && argv[0] == '-')
	{
		if (argv[i] == 'n')
			ok = 1;
		else
			return (0);
		i++;
	}
	if (ok == 1)
		return (1);
	else
		return (0);
}

int	ft_echo(char **argv, int fd)
{
	int	i;
	int	j;
	int	nl;
	int	index;

	i = 1;
	nl = 1;
	index = 1;
	while (argv[i])
	{
		j = 1;
		if (argv[1][0] == '-' && is_valid_flag(argv[i]) == 1)
		{
			index = i + 1;
			nl = 0;
		}
		else
			break ;
		i++;
	}
	while (argv[index])
	{
		ft_putstr_fd(argv[index], fd);
		if (argv[index + 1])
			ft_putchar_fd(' ', fd);
		index++;
	}
	if (nl)
		ft_putchar_fd('\n', fd);
	return (0);
}

int	buildin(char **argv, t_sh_params **shell_params, int *tab_fd)
{
	int		status;
	char	***copy_env;
	int		fd;

	status = 0;
	fd = tab_fd[1];
	copy_env = &((*shell_params)->my_envp);
	if (ft_strcmp(argv[0], "cd") == 0)
		status = ft_cd(argv, copy_env);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		status = ft_pwd(fd);
	else if (ft_strcmp(argv[0], "env") == 0)
		status = ft_env(*copy_env, argv, fd);
	else if (ft_strcmp(argv[0], "unset") == 0)
		status = ft_unset(argv, copy_env);
	else if (ft_strcmp(argv[0], "export") == 0)
		status = ft_export(argv, copy_env, fd);
	else if (ft_strcmp(argv[0], "echo") == 0)
		status = ft_echo(argv, fd);
	else if (ft_strcmp(argv[0], "exit") == 0)
		status = ft_exit(argv, copy_env, shell_params, tab_fd);
	return (status);
}
