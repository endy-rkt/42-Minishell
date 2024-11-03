/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:23:47 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/03 14:50:13 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*cmd_initiate(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->assign = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*cmd_last(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->next)
			return (cmd_last(cmd->next));
		else
			return (cmd);
	}
	return (NULL);
}

void	cmd_addback(t_cmd **cmd, t_cmd *new_cmd)
{
	if (cmd)
	{
		if (*cmd)
			cmd_last(*cmd)->next = new_cmd;
		else
			*cmd = new_cmd;
	}
}

void	cmd_clear(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*next;

	next = NULL;
	if (cmd && *cmd)
	{
		tmp = *cmd;
		while (tmp != NULL)
		{
			next = tmp->next;
			free_one_cmd(&tmp);
			tmp = next;
		}
		*cmd = NULL;
	}
}

int	cmd_is_pipe(t_cmd *cmd)
{
	if (cmd == NULL)
		return (1);
	return (!cmd->args && !cmd->assign && !cmd->redir);
}
