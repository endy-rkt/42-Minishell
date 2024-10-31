/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:21:37 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/31 09:36:09 by trazanad         ###   ########.fr       */
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

void	add_new_identifier(char *key, char *value,  char ***envp)
{
	int		i;
	int		len;
	char	*new_val;
	char	**new;

	new_val = ft_strdup(key);
	if (value[0] == '+')
		new_val = ft_strjoin(new_val, value + 1);
	else
		new_val = ft_strjoin(new_val, value);
	i = 0;
	len = 0;
	while ((*envp)[len])
		len++;
	new = malloc(sizeof(char *) * (len + 2));
	while ((*envp)[i])
	{
		new[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new[i] = new_val;
	new[i + 1] = NULL;
	free_args(*envp);
	*envp = NULL;
	*envp = new;
}

int	export_match(char *str_env, char *key)
{
	int	key_len;

	key_len = ft_strlen(key);
	if (ft_strncmp(str_env, key, key_len) == 0)
	{
		if (str_env[key_len] == '\0' || str_env[key_len] == '=')
			return (1);
	}
	return (0);
}

void	add_value(char *val, char ***envp)
{
	int		i;
	char	*key;
	char	*value;
	char	*new_val;

	i = 0;
	while (val[i] && val[i] != '+' && val[i] != '=')
		i++;
	key = ft_substr(val, 0, i);
	value = val + i;
	while ((*envp)[i])
	{
		if (export_match((*envp)[i], key))
		{
			if (value[0] == '+')
			{
				new_val = ft_strdup((*envp)[i]);
				if ((*envp)[i][ft_strlen(key)] == '\0')
					new_val = ft_strjoin(new_val, "=");
				new_val = ft_strjoin(new_val, value + 2);
				free((*envp)[i]);
				(*envp)[i] = new_val;
			}
			if (value[0] == '=')
			{
				new_val = ft_strdup(key);
				new_val = ft_strjoin(new_val, value);
				free((*envp)[i]);
				(*envp)[i] = new_val;
			}
			free(key);
			return ;
		}
		i++;
	}
	add_new_identifier(key, value, envp);
	free(key);
}

int	update_export(char **argv, char ***my_envp, int fd)
{
	int	i;
	int	name_valid;
	int	is_in_env;

	i = 1;
	name_valid = 0;
	is_in_env = 0;
	while (argv[i])
	{
		name_valid = validate_name(argv[i]);
		if (!name_valid)
		{
			ft_putstr_fd("export: invalid identifier\n", 2);
			return (1);
		}
		add_value(argv[i], my_envp);
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
