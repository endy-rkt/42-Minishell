/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:57:30 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/02 15:35:21 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	execute_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	if (ast->node_type == NODE_CMD && ast->cmd != NULL)
		execute_cmd(ast->cmd);
	else
	{
		//execute_pipe;
	}
}