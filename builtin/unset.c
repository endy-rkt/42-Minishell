/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:14:28 by ferafano          #+#    #+#             */
/*   Updated: 2024/11/02 13:59:58 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int	unset_nb(char **argv, char **env)
{
	int		i;
	int		j;
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
		j = 0;
		while (env[j])
		{
			if (ft_strncmp(argv[i], env[j], ft_strlen(argv[i])) == 0)
			{
				count++;
				break ;
			}
			j++;
		}
		free(tmp);
		i++;
	}
	return (count);
}

int	is_to_unset(char *str, char **argv)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	tmp = ft_strdup(str);
	tmp[i] = '\0';
	i = 0;
	while (argv[i])
	{
		if (ft_strcmp(tmp, argv[i]) == 0)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

int	env_length(char **env)
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

char	**unseted_env(char **argv, char ***copy_env)
{
	int		i;
	int		len;
	int		nb_to_unset;
	char	**new;

	nb_to_unset = unset_nb(argv, *copy_env);
	if (nb_to_unset == 0)
		return (0);
	len = env_length(*copy_env);
	new = malloc(sizeof(char *) * (len - nb_to_unset + 1));
	if (!new)
		return (NULL);
	len = 0;
	i = 0;
	while ((*copy_env)[len])
	{
		if (!is_to_unset((*copy_env)[len], argv))
		{
			new[i] = ft_strdup((*copy_env)[len]);
			i++;
		}
		len++;
	}
	new[i] = NULL;
	return (new);
}

int	ft_unset(char **argv, char ***copy_env)
{
	char	**new;

	if (argv[0] == NULL || argv[1] == NULL)
		return (0);
	new = unseted_env(argv, copy_env);
	if (new == NULL)
		return (0);
	free_args(*copy_env);
	*copy_env = new;
	return (0);
}
