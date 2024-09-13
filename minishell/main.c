/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:30:03 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/13 11:14:47 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh_params	*init_sh_params(char **envp, int exit_status)
{
	t_sh_params	*shell_params;

	shell_params = malloc(sizeof(t_sh_params));
	if (!shell_params)
		return (NULL);
	shell_params->ast = NULL;
	shell_params->tmp_file = NULL;
	shell_params->exit_status = exit_status;
	shell_params->my_envp = NULL;	//copy envp
	shell_params->my_export = NULL; //copy envp
	return (shell_params);
}

int	run_shell(char *input, char **envp, int exit_status)
{
	t_sh_params	*shell_params;
	int			exit_status;

	exit_status = 0;
	shell_params = init_sh_params(envp, exit_status);
	parse(&shell_params, input);
	if (shell_params->exit_status == 0)
		execute(&shell_params);// bad file , cmd not found , built 
	exit_status = shell_params->exit_status;
	close_fd(shell_params);
	delete_tmp_file(shell_params->tmp_file);
	free_shell_params(&shell_params);
	shell_params = NULL;
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	int	exit_status;

	if (argc != 1)
	{
		ft_putchar_fd("minishell: minishell need no argument", 2);
		exit(EXIT_FAILURE);
	}
	exit_status = 0;
	exit_status = process_loop(run_shell, envp, exit_status);//
	exit(exit_status);
}
