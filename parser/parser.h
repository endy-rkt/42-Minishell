/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:03:44 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/20 09:45:57 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "../header.h"

# include "../lexer/lexer.h"

t_cmd	*create_cmd_list(t_token *tk, t_sh_params **shell_params);
int		take_redir(t_token **tk, t_cmd **cmd);
int		take_heredoc(t_token **tk, t_cmd **cmd);
int		take_assign(t_token **tk, t_cmd **cmd);
int		take_args(t_token **tk, t_cmd **cmd, int arg);
t_cmd	*cmd_initiate(void);
t_cmd	*cmd_last(t_cmd *cmd);
void	cmd_addback(t_cmd **cmd, t_cmd *new_cmd);
void	cmd_clear(t_cmd **cmd);
int		cmd_is_pipe(t_cmd *cmd);
int		size_of_args(t_token *tk);
void	free_one_cmd(t_cmd **cmd);
void	free_args(char **args);
void	free_assign(void *value);
void	free_redir(void *redir);
void	print_one_cmd(t_cmd *cmd);
void	print_single_cmd(t_cmd *cmd);
void	print_ast(t_ast *ast);
void	parse(t_sh_params **shell_params, char *input);
void	ast_clear(t_ast **ast);
void	print_error(char *arg_name, char *message);
void	free_sh_params(t_sh_params **shell_params);
void	clean_alloc(t_cmd **cmd, char *file, t_sh_params **shell_params, t_cmd **lst_cmd);
int		*redir_value(t_list *lst_redir);
int		last_redir_in(t_list *lst_redir);
int		last_redir_out(t_list *lst_redir);
t_list	*last_redirin(t_list *lst);
void	invalid_fd(int fd, char *file);
void	add_tmp_file(char *file, t_sh_params **shell_params, t_cmd **cmd);
void	tmp_heredoc(t_list *lst_redir, t_sh_params *shell_params);
void	stored_heredoc(t_cmd **cmd, t_list *lst_redir, char *file, t_sh_params **shell_params);
void	hdoc_status(int status, int pid, t_sh_params **shell_params);
void    process_heredoc(t_cmd **cmd, t_sh_params **shell_params);
char	*heredoc_value(t_redir *rd, t_sh_params *shell_params);
char	*hdoc_new_val(t_redir *rd, char *input, t_sh_params *shell_params);
char	*take_delim(t_redir *rd);
void	manage_heredoc(t_list	*lst_redir, t_cmd **cmd, char *file, t_sh_params **shell_params);

#endif