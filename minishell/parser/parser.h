/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:03:44 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 16:59:15 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "../header.h"

# include "../lexer/lexer.h"

t_cmd	*create_cmd_list(t_token *tk, t_sh_params **sh_params);
int		take_redir(t_token **tk, t_cmd **cmd);
int		take_heredoc(t_token **tk, t_cmd **cmd);
int		take_assign(t_token **tk, t_cmd **cmd);
int		take_args(t_token **tk, t_cmd **cmd, int arg);
t_cmd	*cmd_initiate(void);
t_cmd	*cmd_last(t_cmd *cmd);
void	cmd_addback(t_cmd **cmd, t_cmd *new_cmd);
void	cmd_clear(t_cmd **cmd);
int		cmd_is_pipe(t_cmd *cmd);
void	parse(t_sh_params **sh_params, char *input);
int		size_of_args(t_token *tk);
void	free_one_cmd(t_cmd **cmd);
void    process_heredoc(t_cmd **cmd, t_sh_params **sh_params);
void	change_heredoc(t_cmd **cmd, char *file, t_sh_params **sh_params);
char	*hdoc_new_val(t_redir *rd, char *input, t_sh_params *sh_params);
char	*take_delim(t_redir *rd);

#endif