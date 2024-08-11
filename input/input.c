/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:32:46 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/11 14:12:14 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	handle_input()
{
	int		no_exit;
	char	*input;

	no_exit = 1;
	while (no_exit)
	{
		input = get_next_line(0);
		if (strcmp(input, "exit") == 0)
			no_exit = 0;
		free(input);
	}
}

void	handle_input0(void (*process_input)(char*))
{
	int		no_exit;
	char	*input;

	no_exit = 1;
	while (no_exit)
	{
		input = get_next_line(0);
		if (!input)
			return ;
		process_input(input);
		if (strcmp(input, "exit\n") == 0)//0
			no_exit = 0;
		free(input);
	}
}
