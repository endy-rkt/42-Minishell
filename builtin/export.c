/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:21:37 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/03 15:58:10 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

static char	*get_new_value(char *key, char *value)
{
	char	*new_val;

	new_val = ft_strdup(key);
	if (value[0] == '+')
		new_val = ft_strjoin(new_val, value + 1);
	else
		new_val = ft_strjoin(new_val, value);
	return (new_val);
}

void	add_new_identifier(char *key, char *value, char ***envp)
{
	int		i;
	int		len;
	char	*new_val;
	char	**new;

	i = 0;
	len = 0;
	new_val = get_new_value(key, value);
	while ((*envp)[len])
		len++;
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return ;
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
	i = 0;
	while ((*envp)[i])
	{
		if (export_match((*envp)[i], key) && (value[0] == '+' || value[0] == '='
				|| value[0] == '\0'))
		{
			new_val = export_new_val(value, &key, (*envp)[i]);
			free((*envp)[i]);
			(*envp)[i] = new_val;
			return ;
		}
		i++;
	}
	add_new_identifier(key, value, envp);
	free(key);
}

int	update_export(char **argv, char ***my_envp)
{
	int	i;
	int	name_valid;
	int	status;

	i = 1;
	name_valid = 0;
	status = 0;
	while (argv[i])
	{
		name_valid = validate_name(argv[i]);
		if (!name_valid)
		{
			status = 1;
			ft_putstr_fd("export: invalid identifier\n", 2);
		}
		else
			add_value(argv[i], my_envp);
		i++;
	}
	return (status);
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
	status = update_export(argv, my_envp);
	return (status);
}
