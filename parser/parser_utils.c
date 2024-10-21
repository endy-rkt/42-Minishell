/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:59:44 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/21 11:11:41 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_error(char *arg_name, char *message)
{
	char	*str;

	str = ft_strdup(arg_name);
	str = ft_strjoin(str, ":");
	str = ft_strjoin(str, message);
	ft_putstr_fd(str, 2);
	free(str);
}

void	hdoc_status(int status, int pid, t_sh_params **shell_params)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	    status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
	    status = WTERMSIG(status) + 128;
	(*shell_params)->exit_status = status;
}

void	ast_clear(t_ast **ast)
{
	if (*ast)
	{
		if ((*ast)->left_node != NULL)
		{
			ast_clear(&((*ast)->left_node));
			(*ast)->left_node = NULL;
		}
		if ((*ast)->right_node != NULL)
		{
			ast_clear(&((*ast)->right_node));
			(*ast)->right_node = NULL;
		}
		free(*ast);
		*ast =  NULL;
	}
}

void	free_sh_params(t_sh_params **shell_params)
{
	if ((*shell_params)->ast)
		ast_clear(&((*shell_params)->ast));
	if ((*shell_params)->tmp_file)
		ft_lstclear(&((*shell_params)->tmp_file), free_assign);
	free(*shell_params);
	*shell_params = NULL;
}

void	clean_alloc(t_cmd **cmd, char *file, t_sh_params **shell_params, t_cmd **lst_cmd)
{
	if ((*shell_params)->my_envp)
		free_args(((*shell_params)->my_envp));	
	cmd_clear(lst_cmd);
	free_sh_params(shell_params);
	free(file);
}
