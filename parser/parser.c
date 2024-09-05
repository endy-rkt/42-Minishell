/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:09:16 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/05 10:30:22 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	cmd_pipe(t_cmd *cmd)
{
	if (cmd == NULL)
		return (1);
	return (!cmd->args && !cmd->assign && !cmd->redir_in && !cmd->redir_out);
}

t_ast	*create_node(t_cmd *cmd, t_ast *left, t_ast *right, int node_type)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->cmd = cmd;
	ast->left_node = left;
	ast->right_node = right;
	ast->node_type = node_type;
	return (ast);
}

t_ast	*parse_pipeline(t_cmd **cmd)
{
	t_ast	*tmp;
	t_ast	*left_node;
	t_ast	*right_node;

	left_node = create_node(*cmd, NULL, NULL, NODE_CMD);
	*cmd = (*cmd)->next;
	while (left_node != NULL && *cmd)
	{
		if (cmd_pipe(*cmd))
			*cmd = (*cmd)->next;
		if (!*cmd)
			break ;
		right_node = create_node(*cmd, NULL, NULL, NODE_CMD);
		*cmd = (*cmd)->next;
		tmp = create_node(NULL, left_node, right_node, NODE_PIPELINE);
		left_node = tmp;
	}
	return (left_node);
}

t_ast	*create_ast(t_token	*tk)
{
	t_ast	*ast;
	t_cmd	*cmd;

	if (!tk)
		return (NULL);	
	cmd = parser_test(tk);
	if (!cmd)
		return (NULL);
	ast = parse_pipeline(&cmd);
	return (ast);
}

void	print_ast(t_ast *ast)
{
	static int i=0;
	
	if (ast)
	{
		if (ast->node_type == NODE_CMD)
			print_one_cmd(ast->cmd);
		if (ast->node_type == NODE_PIPELINE)
		{
			printf("************************\n");
			printf("left:\n");
			print_ast(ast->left_node);
			printf("right:\n");
			print_ast(ast->right_node);
			printf("************************\n");
		}
	}	
}
