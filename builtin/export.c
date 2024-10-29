/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:21:37 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/29 12:45:21 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int	validate_name(char *val)
{
	int	i;

	if (val[0] != '_' && !ft_isalpha(val[0]))
		return (0);
	i = 1;
	while (val[i] && val[i] != '=' && val[i] != '+')
	{
		if (val[i] != '_' && !ft_isalnum(val[i]))
			return (0);
		i++;
	}
	if (val[i] == '+' && val[i + 1] != '=')
		return (0);
	return (1);
}

int	search_val(char *val, char **envp)
{
	int		i;
	int		val_len;
	char	*tmp;

	i = 0;
	tmp = malloc(ft_strlen(val) + 2);
	tmp = ft_strcpy(tmp, val);
	while (val[i] && val[i] != '+' && val[i] != '=')
		i++;
	val[i] = '=';
	val[i + 1] = '\0';
	i = 0;
	val_len = ft_strlen(tmp);
	while (envp[i])
	{
		if (ft_strncmp(tmp, envp[i], val_len) == 0)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

void	change_export(char *val, char **envp)
{
	
}

int	update_export(char **argv, char ***my_envp, int fd)
{
	int	i;
	int	name_valid;
	int	is_in_env;

	i = 0;
	name_valid = 0;
	is_in_env = 0;
	while (argv[i])
	{
		name_valid = validate_name(argv[i]);
		if (!name_valid)
		{
			//msg
			return (1);
		}
		is_in_env = search_val(argv[i], *my_envp);
		if (is_in_env)
			change_export(argv[i], my_envp);
		else
			add_export(argv[i], my_envp);
		i++;
	}
	return (0);
}

int	ft_export(char **argv, char ***my_envp, int fd)
{
	int	status;

	status = 0;
	if (argv == NULL || argv[0] == NULL)
		return (status);
	if (argv[1] == NULL)
	{
		print_export(*my_envp, fd);
		return (status);
	}
	status = update_export(argv, my_envp, fd);
	return (status);
}
