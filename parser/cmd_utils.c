/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 07:20:23 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/22 12:03:00 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*create_cmd(t_token *tk)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->assign = NULL;//0
	cmd->cmd_name = NULL;//0
	cmd->args = NULL;//0
	cmd->redir = NULL;//0
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
}

void	cmd_add_back(t_cmd **cmd, t_cmd	*new_cmd)
{
	if (cmd)
	{
		if (*cmd)
			cmd_last(*cmd)->next = new_cmd;
		else
			*cmd = new_cmd;
	}
}

void	cmd_clear(t_cmd	**cmd)
{
	t_cmd	*tmp;
	t_cmd	*cmd_next;

	if (cmd)
	{
		if (*cmd)
		{
			tmp = *cmd;
			while (tmp)
			{
				cmd_next = tmp->next;
				if (tmp->cmd_name)
					free(tmp->cmd_name);
				// free(tmp->assign);
				// free(tmp->args);
				// free(tmp->redir);
				free(tmp);
				tmp = cmd_next;
			}
		}
	}
}

void	print_single_cmd(t_cmd *cmd)
{
	printf("----------------------------------------------------------------\n");
	if (cmd->cmd_name)
		printf("cmd:%s\n", cmd->cmd_name);
	printf("assign:%s\n");
	printf("args:%s\n");
	printf("redir:%s\n");
}

void	cmd_print(t_cmd *cmd)
{
	if (cmd)
		print_single_cmd(cmd);
	else
		return ;
	cmd_print(cmd->next);
}

/*
	create:			cmd->assign, cmd->redir, cmd->args
		-free (clear)
		-print
		-create

	create:
		-tk to assign
		-tk to cmd_name
		-tk to redir
		-tk to args
*/