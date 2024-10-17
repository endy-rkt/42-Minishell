/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:03:52 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/17 09:44:58 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_sh_params(t_sh_params **shell_params)
{
	if ((*shell_params)->ast)
		ast_clear(&((*shell_params)->ast));
	if ((*shell_params)->tmp_file)
		ft_lstclear(&((*shell_params)->tmp_file), free_assign);
	// if ((*shell_params)->my_envp)
	// 	free_args(((*shell_params)->my_envp));
	free(*shell_params);
	*shell_params = NULL;
}

static t_ast	*create_node(t_cmd *cmd, t_ast *left, t_ast *right, int node_type)
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

static t_ast	*parse_pipeline(t_cmd **cmd)
{
	t_ast	*tmp;
	t_ast	*left_node;
	t_ast	*right_node;

	left_node = create_node(*cmd, NULL, NULL, NODE_CMD);
	*cmd = (*cmd)->next;
	while (left_node != NULL && *cmd)
	{
		if (cmd_is_pipe(*cmd))
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

static t_ast	*create_ast(t_cmd *cmd)
{
	t_ast	*ast;

	if (!cmd)
		return (NULL);
	ast = parse_pipeline(&cmd);
	return (ast);
}

void	ast_clear(t_ast **ast)
{
	if (*ast)
	{
		if ((*ast)->left_node != NULL)
		{
			ast_clear(&((*ast)->left_node));
			(*ast)->left_node = NULL;
		}
		if ((*ast)->right_node != NULL)
		{
			ast_clear(&((*ast)->right_node));
			(*ast)->right_node = NULL;
		}
		free(*ast);
		*ast =  NULL;
	}
}


void	parse(t_sh_params **shell_params, char **input)
{
	t_token	*tk;
	t_cmd	*cmd;
	t_ast	*ast;
	int		tk_error;

	tk_error = 0;
	tk = lex(*input, shell_params);
	free(*input);
	*input = NULL;
	if (!tk)
		return ;
	tk_error = check_tk_error(&tk, shell_params);
	expand(&tk, *shell_params);
	(*shell_params)->exit_status = tk_error;
	cmd = create_cmd_list(tk, shell_params);
	tk_clear(&tk);
	if (tk_error)
	{
		cmd_clear(&cmd);
		return ;
	}
	process_heredoc(&cmd, shell_params);
	ast = create_ast(cmd);
	(*shell_params)->cmd = cmd;
	(*shell_params)->ast = ast;
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
			printf("type:%d\n", ast->node_type);
			print_ast(ast->left_node);
			printf("right:\n");
			print_ast(ast->right_node);
			printf("************************\n");
		}
	}	
}
