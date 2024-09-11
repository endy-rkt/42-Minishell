/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:23:47 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 16:29:23 by trazanad         ###   ########.fr       */
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
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
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

	if (cmd && *cmd)
	{
		tmp = *cmd;
		while (tmp)
		{
			next = tmp->next;
			//free(tmp);
			tmp = next;
		}
		*cmd = NULL;
	}
}

int	cmd_is_pipe(t_cmd *cmd)
{
	if (cmd == NULL)
		return (1);
	return (!cmd->args && !cmd->assign && !cmd->redir_in && !cmd->redir_out);
}

void	print_one_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		printf("----------------------------------------------------------------\n");
		if (!cmd->args && !cmd->assign && !cmd->redir_in && !cmd->redir_out)
		{
			printf("pipe\n");
		}
		if (cmd->args)
		{
			int i =0;
			printf("args:\t");
			while (cmd->args[i] != NULL)
			{
				printf("{%s}\t", cmd->args[i]);
				i++;
			}
			printf("\n");
		}
		if (cmd->assign)
		{
			t_list *assign = cmd->assign;
			printf("assign:\t");
			while (assign)
			{
				printf("{%s}\t", (char*)assign->content);
				assign = assign->next;
			}
			printf("\n");
		}
		if (cmd->redir_in)
		{
			t_list *redir= cmd->redir_in;
			t_redir *tmp;
			printf("redir_in:\t");
			while (redir)
			{
				tmp = (t_redir *)redir->content;
				printf("{%s}{%d}{%d}\t", tmp->file, tmp->fd, tmp->type);
				redir = redir->next;
			}
			printf("\n");
		}
		if (cmd->redir_out)
		{
			t_list *redir= cmd->redir_out;
			t_redir *tmp;
			printf("redir_out:\t");
			while (redir)
			{
				tmp = (t_redir *)redir->content;
				printf("{%s}{%d}{%d}\t", tmp->file, tmp->fd, tmp->type);
				redir = redir->next;
			}
			printf("\n");
		}
		// printf("args:%s\n");
		// printf("assign:%s\n");
		// printf("redir:%s\n");
	}
}

void	print_single_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		print_one_cmd(cmd);
		cmd = cmd->next;
	}
}
