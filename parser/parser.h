/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:07:30 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/22 00:10:20 by trazanad         ###   ########.fr       */
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

#endif