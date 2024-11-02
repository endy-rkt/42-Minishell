/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:41:41 by ferafano          #+#    #+#             */
/*   Updated: 2024/11/02 14:59:06 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

char	*get_env_value(char *line_read, char **copy_env)
{
	int	i;
	int	len;

	len = 0;
	while (line_read[len] && line_read[len] != '=')
		len++;
	i = 0;
	while (copy_env[i])
	{
		if (export_match(copy_env[i], line_read))
		{
			return (copy_env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}
