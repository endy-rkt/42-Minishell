/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:52:23 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/06 15:37:33 by trazanad         ###   ########.fr       */
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
	
	ft_printf("---%s---\n", value);
	free(value);
	return (0);
}
