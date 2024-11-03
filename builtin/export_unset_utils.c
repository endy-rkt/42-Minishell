/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:11:43 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/03 15:58:30 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

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

char	*export_new_val(char *value, char **key, char *prev_val)
{
	char	*new_val;

	new_val = NULL;
	if (value[0] == '+')
	{
		new_val = ft_strdup(prev_val);
		if (prev_val[ft_strlen(*key)] == '\0')
			new_val = ft_strjoin(new_val, "=");
		new_val = ft_strjoin(new_val, value + 2);
	}
	else if (value[0] == '=')
	{
		new_val = ft_strdup(*key);
		new_val = ft_strjoin(new_val, value);
	}
	else
		new_val = ft_strdup(prev_val);
	free(*key);
	*key = NULL;
	return (new_val);
}

int	update_unset_count(char *str, char **env)
{
	int	len;
	int	count;
	int	i;

	i = 0;
	count = 0;
	len = ft_strlen(str);
	while (env[i])
	{
		if (ft_strncmp(str, env[i], len) == 0)
		{
			count++;
			break ;
		}
		i++;
	}
	return (count);
}

int	unset_nb(char **argv, char **env)
{
	int		i;
	int		count;
	char	*tmp;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (argv[i][0] == '\0')
		{
			if (argv[i + 1] == NULL)
				break ;
			else
				i++;
		}
		tmp = ft_strdup(argv[i]);
		tmp = ft_strjoin(tmp, "=");
		count += update_unset_count(argv[i], env);
		free(tmp);
		i++;
	}
	return (count);
}
