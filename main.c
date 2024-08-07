/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:52:23 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/06 23:18:10 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[]/*, char *envp[]void*/)
{
	t_token	*tk;
	char	*str;

	if (argc < 1)
		return (0);
	//str = ft_strdup(argv[1]);
	tk = lex(argv[1]);
	tk_print(tk);
	tk_clear(&tk);
	return (0);
}
