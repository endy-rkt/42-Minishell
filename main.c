/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:30:03 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/03 14:04:58 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh_params	*init_sh_params(char **envp, char **genvp, int exit_status)
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
	shell_params->globl_envp = genvp;
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

void	clean_params(t_sh_params *shell_params)
{
	if (shell_params->tmp_file)
		delete_tmp_file(shell_params->tmp_file);
	cmd_clear(&(shell_params->cmd));
	if (shell_params)
		free_sh_params(&shell_params);
}

int	run_shell(char *input, char ***envp, int prev_status)
{
	int			exit_status;
	char		**tmp_envp;
	t_sh_params	*shell_params;

	exit_status = prev_status;
	tmp_envp = ft_copy_env(*envp);
	shell_params = init_sh_params(tmp_envp, *envp, exit_status);
	parse(&shell_params, input);
	if (shell_params->exit_status == 0 && shell_params->ast != NULL)
		execute(&shell_params);
	exit_status = shell_params->exit_status;
	free_args(*envp);
	*envp = shell_params->my_envp;
	clean_params(shell_params);
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("minishell: minishell need no argument", 2);
		exit(EXIT_FAILURE);
	}
	process_loop(run_shell, envp);
	exit(0);
}
