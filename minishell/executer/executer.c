/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:06:43 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 17:14:45 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	execute(t_sh_params **sh_params)
{
	t_ast	*ast;

	ast = (*sh_params)->ast;
	if (ast == NULL)
		return ;
	if (ast->node_type == NODE_CMD && ast->cmd != NULL)
		execute_cmd(sh_params);
	else
		execute_pipeline(sh_params);
}
