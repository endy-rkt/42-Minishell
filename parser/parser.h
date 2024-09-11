/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:07:30 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 12:54:36 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "../lexer/lexer.h"

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
void	print_ast(t_ast *ast);
t_ast	*create_ast(t_token	*tk);
int		cmd_pipe(t_cmd *cmd);
void    process_heredoc(t_cmd **cmd);

#endif