/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:03:52 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/02 14:47:26 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast	*create_node(t_cmd *cmd, t_ast *left, t_ast *right,
		int t_node_type)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->cmd = cmd;
	ast->left_node = left;
	ast->right_node = right;
	ast->t_node_type = t_node_type;
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

static int	error_in_lexing(int tk_error, t_cmd **cmd)
{
	if (tk_error)
	{
		cmd_clear(cmd);
		return (1);
	}
	return (0);
}

int	check_void_redir(t_token *tk, t_sh_params **shell_params)
{
	while (tk)
	{
		if (is_redir(tk))
		{
			if (tk->next == NULL || tk->next->value == NULL)
				return (my_perror(2,
					"minishell: syntax error near unexpected token `<'\n"));
		}
		tk = tk->next;
	}
	return (0);
}

void	parse(t_sh_params **shell_params, char *input)
{
	t_token	*tk;
	t_cmd	*cmd;
	t_ast	*ast;
	int		tk_error;

	tk_error = 0;
	tk = lex(input, shell_params);
	if (!tk)
		return ;
	tk_error = check_tk_error(&tk, shell_params);
	if (tk_error != 0)
	{
		(*shell_params)->exit_status = tk_error;
		tk_clear(&tk);
		return ;
	}
	expand(&tk, *shell_params);
	tk_error = check_void_redir(tk, shell_params);
	if (tk_error != 0)
	{
		(*shell_params)->exit_status = tk_error;
		tk_clear(&tk);
		return ;
	}
	(*shell_params)->exit_status = tk_error;
	cmd = create_cmd_list(tk);
	tk_clear(&tk);
	if (error_in_lexing(tk_error, &cmd))
		return ;
	process_heredoc(&cmd, shell_params);
	ast = create_ast(cmd);
	(*shell_params)->cmd = cmd;
	(*shell_params)->ast = ast;
}

void	print_ast(t_ast *ast)
{
	static int	i = 0;

	if (ast)
	{
		if (ast->t_node_type == NODE_CMD)
			print_one_cmd(ast->cmd);
		if (ast->t_node_type == NODE_PIPELINE)
		{
			printf("************************\n");
			printf("left:\n");
			printf("type:%d\n", ast->t_node_type);
			print_ast(ast->left_node);
			printf("right:\n");
			print_ast(ast->right_node);
			printf("************************\n");
		}
	}
}
