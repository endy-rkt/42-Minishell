/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:52:23 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/05 16:19:09 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[]/*, char *envp[]void*/)
{
	int		len;
	char	*value;
	char	*str;

	if (argc < 1)
		return (0);
	len = 0;
	printf("---%s---\n", argv[0]);
	str = ft_strdup(argv[1]);
	while (str[len] && !ft_isspace(str[len]) && !is_operator(str[len]))
	{
		while (str[len] != '\'' && str[len] != '\"' && str[len])
			len++;
		if (str[len] == '\'' || str[len] == '\"')
			len += idx_of_first(str + len, str[len]);
	}
	value = ft_substr(str, 0, len);
	ft_printf("---%s---\n", value);
	free(value);
	return (0);
}
