/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:07:30 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/21 16:47:01 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "../header.h"

typedef enum {
    NODE_CMD,
    NODE_PIPE,
    NODE_AND,
    NODE_OR,
}	node_type;

typedef struct s_assign
{
	char			*key;
	char			*value;
	struct s_assign	*next;
}	t_assign;

typedef struct s_cmd
{
	t_assign	*assign;
	char		*cmd_name;
	char		**args;
	t_list		*input;
	t_list		*ouput;
	t_list		*heredoc;
	t_list		*last_input;
	t_list		*last_ouput;
}	t_cmd;

#endif