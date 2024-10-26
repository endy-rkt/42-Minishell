/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:10:55 by ferafano          #+#    #+#             */
/*   Updated: 2024/10/25 11:26:06 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

void	ft_copy(char *str, char *dest)
{
	int	i;

	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
}

char	**ft_allocate_env_copy(char **envp, int *len)
{
	char	**copy;

	*len = 0;
	while (envp[*len])
		(*len)++;
	copy = (char **)malloc((*len + 1) * sizeof(char *));
	if (copy == NULL)
		return (NULL);
	return (copy);
}

char	**ft_copy_env_content(char **envp, char **copy, int len)
{
	int	j;
	int	k;
	int	str_len;

	j = 0;
	k = 0;
	while (j < len)
	{
		str_len = ft_strlen(envp[j]);
		copy[j] = (char *)malloc((str_len + 1) * sizeof(char));
		if (copy[j] == NULL)
		{
			while (k < j)
				free(copy[k++]);
			free(copy);
			return (NULL);
		}
		ft_copy(envp[j], copy[j]);
		j++;
	}
	copy[len] = NULL;
	return (copy);
}

// char	**ft_copy_env(char **envp)
// {
// 	int		len;
// 	char	**copy;

// 	copy = ft_allocate_env_copy(envp, &len);
// 	if (copy == NULL)
// 		return (NULL);
// 	return (ft_copy_env_content(envp, copy, len));
// }

char	**ft_copy_env(char **envp)
{
	int		i;
	int		envp_len;
	char	**cpy_enpv;

	envp_len = 0;
	if (envp == NULL)
		return (NULL);
	while (envp[envp_len])
		envp_len++;
	cpy_enpv = malloc(sizeof(char*) * (envp_len + 1));
	i = 0;
	while (envp[i])
	{
		cpy_enpv[i] = ft_strdup(envp[i]);
		i++;
	}
	cpy_enpv[i] = NULL;
	return (cpy_enpv);
}
