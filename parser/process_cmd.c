/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:46:52 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/23 10:49:13 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"

t_cmd	*create_cmd(t_token *tk)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;//0
	cmd->redir = NULL;//0
	cmd->assign = NULL;//0
	return (cmd);
}

void	cmd_clear(t_cmd	**cmd)
{
	if (cmd)
	{
		if (*cmd)
		{
			if ((*cmd)->args)
				clear_args(&((*cmd)->args));
			if ((*cmd)->assign);
				ft_lstclear(&((*cmd)->assign), clear_assign);
			if ((*cmd)->redir)
				ft_lstclear(&((*cmd)->redir), clear_redir);
		}
	}
}

void	print_single_cmd(t_cmd *cmd)
{
	printf("----------------------------------------------------------------\n");
	printf("cmd:%s\n");
	printf("args:%s\n");
	printf("assign:%s\n");
	printf("redir:%s\n");
}
