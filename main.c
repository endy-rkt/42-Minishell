/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:52:23 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/05 23:59:08 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[]/*, char *envp[]void*/)
{
	int		len;
	char	*value;
	int 	redir_nb;
	char	*str;

	if (argc < 1)
		return (0);
	len = 0;
	str = ft_strdup(argv[1]);
	len = 0;
	redir_nb = 0;
	while (ft_isdigit(str[len]))
		len++;
	while (str[len] == '<' || str[len] == '>')
	{
		len++;
		redir_nb++;
	}
	while (str[len] && !ft_isspace(str[len]) && !is_operator(str[len]))
	{
		while (str[len] != '\'' && str[len] != '\"' && str[len])
			len++;
		if (str[len] == '\'' || str[len] == '\"')
			len += idx_of_first(str + len, str[len]);
	}
	value = ft_substr(str, 0, len);
	ft_printf("---%s---%d\n", value, redir_nb);
	free(value);
	return (0);
}
