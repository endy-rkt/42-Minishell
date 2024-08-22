/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:07:30 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/23 00:01:09 by trazanad         ###   ########.fr       */
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
	t_list			*assign;
	char			*cmd_name;
	char			**args;
	t_list			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef enum {
	NODE_CMD,
	NODE_PIPELINE,
}	node_type;

typedef struct s_ast
{

	struct s_ast	*left_node;
	struct s_ast	*right_node;
}	t_ast;

#endif