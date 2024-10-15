/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:14:39 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/14 08:46:38 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TYPEDEF_H

# define TYPEDEF_H

# include "./libft/libft.h"

typedef enum {
    TK_WORD,
	TK_ASSIGN,
    TK_PIPE,
    TK_REDIR_IN,
    TK_REDIR_IN2, 
    TK_REDIR_OUT,
    TK_REDIR_APPEND,
    TK_HEREDOC
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
	char		*file;
	token_type	type;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_list			*assign;
	t_list			*redir;
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

typedef struct s_shell_params
{
	t_ast	*ast;
	t_list	*tmp_file;
	char	**my_envp;
	int		exit_status;
}	t_sh_params;

#endif