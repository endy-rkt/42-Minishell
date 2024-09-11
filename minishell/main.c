/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:30:03 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 17:26:25 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh_params	*init_sh_params(char **envp)
{
	t_sh_params	*sh_params;

	sh_params = malloc(sizeof(t_sh_params));
	if (!sh_params)
		return (NULL);
	sh_params->ast = NULL;
	sh_params->tmp_file = NULL;
	sh_params->exit_status = 0;
	sh_params->my_envp = NULL;	//copy envp
	sh_params->my_export = NULL; //copy envp
	return (sh_params);
}

int	run_shell(char *input, char **envp)
{
	t_sh_params	*sh_params;
	int			exit_status;

	exit_status = 0;
	sh_params = init_sh_params(envp);
	parse(&sh_params, input);
	if (sh_params->exit_status == 0)
		execute(&sh_params);
	exit_status = sh_params->exit_status;
	close_fd(sh_params);
	delete_tmp_file(sh_params->tmp_file);
	free_sh_params(&sh_params);
	sh_params = NULL;
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
	exit_status = process_loop(run_shell, envp);//
	exit(exit_status);
}
