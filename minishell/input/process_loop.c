/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:16:41 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/11 09:43:41 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int	flag = 0;

static int	keep_running(char *input)
{
	if (strcmp(input, "exit\n") == 0)
		return (0);
	return (1);
}

void handle_sigint(int sig)
{
    (void)sig;
	ft_printf("\n>>");
}

int	process_loop(int (*run_shell)(char *, char **, int), char **envp)
{
	char	*input;
	int		no_exit;
	int		prev_status;

	no_exit = 1;
	prev_status = 0;
	signal(SIGINT, handle_sigint);
	while (no_exit)
	{
		ft_printf(">>");
		input = get_next_line(0);
		if (input == NULL)
			return (1);
		prev_status = run_shell(input, envp, prev_status);
		no_exit = keep_running(input);
		free(input);	
	}
	return (0);
}
