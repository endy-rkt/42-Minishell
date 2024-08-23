/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:09:16 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/23 11:14:51 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*create_node(t_cmd *cmd, t_ast *left, t_ast *right)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->cmd = cmd;
	ast->left_node = left;
	ast->right_node = right;
	return (ast);
}

t_ast	*parse_pipeline(t_token *tk)
{
	t_ast	*tmp;
	t_ast	*left_node;
	t_ast	*right_node;

	left_node = create_node(NULL, NULL, NULL);
	while (left_node && tk)
	{
		if (tk->type == TK_PIPE)
			tk = tk->next;
		if (!tk)
			break ;
		right_node = create_node(NULL, NULL, NULL);
		tmp = create_node(NULL, left_node, right_node);
		if (!tmp)
			return (left_node);
		left_node = tmp;
	}
	return (left_node);
}

t_ast	*create_ast(t_token	*tk)
{
	t_ast	*ast;
	t_token	*current_tk;

	if (!tk)
		return (NULL);	
	current_tk = tk;
	while (current_tk)
	{
		//process_tk;
		current_tk = current_tk->next;
	}
	return (ast);
}

