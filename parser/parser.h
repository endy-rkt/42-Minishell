/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:07:30 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/26 10:18:52 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "../header.h"

# include "../lexer/lexer.h"

typedef struct s_redir
{
	int			fd;
	char		*file;//delimiter
	token_type	type;
}	t_redir;

typedef struct s_cmd
{
	char			**args; //args[0] == cmd_name
	t_list			*assign;
	t_list			*redir;
	t_redir			*input;
	t_redir			*output;
	struct s_cmd	*next;
}	t_cmd;

typedef enum {
	NODE_CMD,
	NODE_PIPELINE,
}	node_type;

typedef struct s_ast
{
	t_cmd			*cmd;
	int				node_type;
	struct s_ast	*left_node;
	struct s_ast	*right_node;
}	t_ast;

// void	clear_args(char	***args);
// void	clear_redir(void *redir);
// void	clear_assign(void *assign);
// t_redir	*create_redir(char *str, token_type type, int is_last);
t_cmd	*parser_test(t_token *tk);
void	print_single_cmd(t_cmd *cmd);
void	print_one_cmd(t_cmd *cmd);
void	cmd_addback(t_cmd **cmd, t_cmd *new_cmd);
t_cmd	*cmd_last(t_cmd *cmd);
t_cmd	*cmd_create(t_token	**tk);
t_ast	*create_ast(t_token	*tk);
void	print_ast(t_ast *ast);
t_ast	*create_ast(t_token	*tk);

#endif