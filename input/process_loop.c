/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:16:41 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/18 08:56:04 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static volatile sig_atomic_t signal_code = 0;

void	sigint_handler(int sig)
{
	static char	*prompt = "\033[0;35m❯ \033[0m";
	
	signal_code = 130;
    (void)sig;
	ft_printf("\n%s", prompt);
}


void	signal_handler()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}	

int	launch_execution(char **input)
{
	if (ft_strcmp(*input, "exit\n") == 0 || ft_strcmp(*input, "\n") == 0)
	{
		ft_printf("exit\n");
		free(*input);
		*input = NULL;
		return (0);
	}
	return (1);
}

int	process_loop(int (*run_shell)(char **, char ***, int), char **envp)
{
	int			no_exit;
	int			prev_status;
	char		*input;
	char		**global_envp;
	static char	*prompt = "\033[0;35m❯ \033[0m";

	no_exit = 1;
	prev_status = 0;
	signal_handler();
	global_envp = ft_copy_env(envp);
	while (no_exit)
	{
		ft_printf("%s", prompt);
		input = get_next_line(0);
		if (input == NULL)
		{
			free_args(global_envp);
			return (1);
		}
		no_exit = ft_strcmp(input, "exit\n");
		if (launch_execution(&input))
			prev_status = run_shell(&input, &global_envp, signal_code);
		signal_code = prev_status;
	}
	free_args(global_envp);
	return (0);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	char	*line_read;
// 	char	**copy_env;
// 	char	**args;

// 	(void)argc;
// 	(void)argv;
// 	line_read = NULL;
// 	copy_env = ft_copy_env(envp);
// 	args = malloc(sizeof(char *));
// 	while (1)
// 	{
// 		if (line_read)
// 		{
// 			free(line_read);
// 			line_read = NULL;
// 		}
// 		pwd_prompt();
// 		line_read = readline("\n\033[0;35m❯ \033[0m");
// 		add_history(line_read);
// 		args = ft_split(line_read, ' ');
// 		//int fd = open("test", O_RDWR | O_TRUNC);
// 		buildin(args, &copy_env, 1);
// 	}
// 	for (int i = 0; copy_env[i]; i++)
// 		free(copy_env[i]);
// 	free(copy_env);
// 	return (0);
// }