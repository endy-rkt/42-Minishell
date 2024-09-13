/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:06:43 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/13 11:14:47 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	execute(t_sh_params **shell_params)
{
	t_ast	*ast;

	ast = (*shell_params)->ast;
	if (ast == NULL)
		return ;
	if (ast->cmd == NULL)
		return ;
	if (ast->node_type == NODE_CMD)
		execute_cmd(shell_params);
	else
		execute_pipeline(shell_params);
}
