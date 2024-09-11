/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:57:30 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 13:12:14 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	execute_ast(t_sh_params *sh_params)
{
	t_ast	*ast;
	char	**my_envp;

	ast = sh_params->ast;
	my_envp = sh_params->my_envp;
	if (ast == NULL)
		return ;
	if (ast->node_type == NODE_CMD && ast->cmd != NULL)
		execute_cmd(ast, my_envp, STDIN_FILENO, STDOUT_FILENO);
	else
	{
		execute_pipe(ast, my_envp);
	}
}
