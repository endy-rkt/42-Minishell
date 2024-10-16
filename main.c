/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:30:03 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/16 12:49:31 by trazanad         ###   ########.fr       */
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
	shell_params->my_envp = envp;
	shell_params->cmd = NULL;
	return (shell_params);
}

void	delete_tmp_file(t_list *tmp_file)
{
	char	*file;

	while (tmp_file)
	{
		if (tmp_file->content != NULL)
			file = tmp_file->content;
		unlink(file);
		tmp_file = tmp_file->next;
	}	
}

int	run_shell(char *input, char ***envp, int prev_status)
{
	int			exit_status;
	t_sh_params	*shell_params;

	exit_status = prev_status;
	shell_params = NULL;
	shell_params = init_sh_params(*envp, exit_status);//copy env
	parse(&shell_params, input);
	// print_ast(shell_params->ast);
	if (shell_params->exit_status == 0 && shell_params->ast != NULL)
		execute(&shell_params);// bad file , cmd not found , built 
	// exit_status = shell_params->exit_status;
	// //close_fd(shell_params);
	if (shell_params->tmp_file)
		delete_tmp_file(shell_params->tmp_file);
	*envp = shell_params->my_envp;
	cmd_clear(&(shell_params->cmd));
	if (shell_params)
		free_sh_params(&shell_params);
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		ft_putstr_fd("minishell: minishell need no argument", 2);
		exit(EXIT_FAILURE);
	}
	process_loop(run_shell, envp);//
	exit(0);
}
