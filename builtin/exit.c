/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:32:11 by ferafano          #+#    #+#             */
/*   Updated: 2024/11/04 10:20:06 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int	valid_exit(char *str)
{
	int		i;
	long	tmp;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (i == 0 && str[1] != '\0' && (str[i] == '-' || str[i] == '+'))
			i++;
		else if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
			return (0);
	}
	if ((str[1] == '-' && ft_strlen(str) > 21) || (ft_strlen(str) > 20)
		|| !ft_strcmp(str, "-9223372036854775809") || !ft_strcmp(str,
			"9223372036854775808") || !ft_strcmp(str, "9223372036854775809"))
		return (0);
	tmp = ft_atol(str);
	if (tmp >= -9223372036854775807 - 1 && tmp <= 9223372036854775807)
		return (1);
	else
		return (0);
}

void	ft_exit_free(char **copy_env)
{
	int	i;

	i = 0;
	while (copy_env[i])
	{
		free(copy_env[i]);
		i++;
	}
	free(copy_env);
}

static void	free_paramas(t_sh_params **shell_params, int *tab_fd)
{
	free(tab_fd);
	free_args((*shell_params)->my_envp);
	free_args((*shell_params)->globl_envp);
	cmd_clear(&((*shell_params)->cmd));
	if (*shell_params)
		free_sh_params(shell_params);
}

int	check_many_args(char **argv, t_sh_params **shell_params)
{
	if (argv[1] && argv[2] && valid_exit(argv[1]) == 1)
	{
		(*shell_params)->exit_status = 1;
		write(2, "exit: too many arguments\n", 25);
		return (1);
	}
	return (0);
}

int	ft_exit(char **argv, t_sh_params **shell_params, int *tab_fd)
{
	int	status;

	exit_trim(argv);
	if (check_many_args(argv, shell_params))
		return (1);
	else if (argv[1] && valid_exit(argv[1]) == 1)
	{
		status = ft_atol(argv[1]);
		free_paramas(shell_params, tab_fd);
		exit(status);
	}
	else if (!argv[1])
	{
		free_paramas(shell_params, tab_fd);
		exit(0);
	}
	else
	{
		write(2, "numeric argument required\n", 26);
		free_paramas(shell_params, tab_fd);
		exit(2);
	}
}
