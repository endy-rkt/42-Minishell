/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:16:41 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/21 10:40:40 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static volatile sig_atomic_t g_status = 0;

static void	sigint_handler(int sig)
{
	static char	*prompt = "\033[0;35m❯ \033[0m";

    (void)sig;
	g_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}


static void	main_sig_handler()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}	

static int	null_input(char *input, char **global_env)
{
	if (input == NULL)
	{
		free_args(global_env);
		ft_printf("exit");
		return (1);
	}
	return (0);
}

static int	exec_process(char *input, char **global_envp)
{
	if (ft_strcmp(input, "exit") == 0)
	{
		ft_printf("exit");
		free_args(global_envp);
		global_envp = NULL;
		exit (g_status);
	}
	if (ft_strcmp(input, "") == 0)
		return (0);
	return (1);
}

int	process_loop(int (*run_shell)(char *, char ***, int), char **envp)
{
	int			no_exit;
	int			prev_status;
	char		*input;
	char		**global_envp;
	static char	*prompt = "\033[0;35m❯ \033[0m";

	no_exit = 1;
	prev_status = 0;
	global_envp = ft_copy_env(envp);
	rl_catch_signals = 1;
	while (no_exit)
	{
		main_sig_handler();
		input = readline(prompt);
		if (null_input(input, global_envp))
			return (1);
		add_history(input);
		no_exit = ft_strcmp(input, "exit");
		if (exec_process(input, global_envp))
			prev_status = run_shell(input, &global_envp, g_status);
		g_status = prev_status;
	}
	return (0);
}

// int	process_loop(int (*run_shell)(char *, char ***, int), char **envp)
// {
// 	int			no_exit;
// 	int			prev_status;
// 	char		*input;
// 	char		**global_envp;
// 	static char	*prompt = "\033[0;35m❯ \033[0m";

// 	no_exit = 1;
// 	prev_status = 0;
// 	main_sig_handler();
// 	global_envp = ft_copy_env(envp);
// 	while (no_exit)
// 	{
// 		ft_printf("%s", prompt);
// 		input = get_next_line(0);
// 		if (input == NULL)
// 		{
// 			free_args(global_envp);
// 			return (1);
// 		}
// 		no_exit = ft_strcmp(input, "exit\n");
// 		if (launch_execution(&input, global_envp))
// 			prev_status = run_shell(&input, &global_envp, g_status);
// 		g_status = prev_status;
// 	}
// 	return (0);
// }