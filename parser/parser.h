/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:07:30 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/23 10:49:08 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "../header.h"

# include "../lexer/lexer.h"

typedef struct s_redir
{
	int			is_last;
	token_type	type;
	char		*str;
}	t_redir;

typedef struct s_cmd
{
	char			**args; //args[0] == cmd_name
	t_list			*assign;
	t_list			*redir;
}	t_cmd;

typedef enum {
	NODE_CMD,
	NODE_PIPELINE,
}	node_type;

typedef struct s_ast
{
	t_cmd			*cmd;
	struct s_ast	*left_node;
	struct s_ast	*right_node;
}	t_ast;

void	clear_args(char	***args);
void	clear_redir(void *redir);
void	clear_assign(void *assign);
t_redir	*create_redir(char *str, token_type type, int is_last);

#endif