/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:44:56 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 13:15:18 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H

# define TYPEDEF_H

# include "./libft/libft.h"

typedef enum {
    TK_WORD,
	TK_ASSIGN,
    TK_PIPE,
    TK_REDIR_IN, // error if no fd
    TK_REDIR_IN2, // create and read
    TK_REDIR_OUT, //create and write
    TK_REDIR_APPEND, //create and append
    TK_HEREDOC,
    TK_HEREDOC2,
}	token_type;

typedef struct s_token
{
	char			*value;
	token_type		type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;


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
	t_list			*redir_in;
	t_list			*redir_out;
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

typedef struct s_sh_params
{
	t_ast	*ast;
	t_list	*tmp_file;
	char	**my_envp;
	char	**my_export;
	int		exit_status;
}	t_sh_params;

#endif