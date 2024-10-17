/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:16:41 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/16 16:56:59 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	sigint_handler(int sig)
{
    (void)sig;
	ft_printf("\n>>");
}

void	signal_handler()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
}	

int	launch_execution(char **input)
{
	if (ft_strcmp(*input, "exit\n") == 0 || ft_strcmp(*input, "\n") == 0)
	{
		free(*input);
		*input = NULL;
		return (0);
	}
	return (1);
}

int	process_loop(int (*run_shell)(char **, char ***, int), char **envp)
{
	int		no_exit;
	int		prev_status;
	char	*input;
	char	**global_envp;

	no_exit = 1;
	prev_status = 0;
	signal_handler();
	global_envp = ft_copy_env(envp);
	while (no_exit)
	{
		ft_printf(">>");
		input = get_next_line(0);
		if (input == NULL)
		{
			free_args(global_envp);
			return (1);
		}
		no_exit = ft_strcmp(input, "exit\n");
		if (launch_execution(&input))
			prev_status = run_shell(&input, &global_envp, prev_status);
	}
	free_args(global_envp);
	return (0);
}
