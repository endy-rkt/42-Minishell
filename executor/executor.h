/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:03:37 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/04 07:58:56 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H

# define EXECUTOR_H

# include "../builtin/buildin.h"
# include "../header.h"
# include "../parser/parser.h"

char	*path_from_env(char **args, char **my_envp, int *err_status);
char	*get_path(char **args, char **my_envp, int *err_status);
int		change_redir(t_list *lst_redir);
void	print_exec_error(char *arg_name, char *message);
int		not_valid_path(char *path);
void	execute(t_sh_params **shell_params);
int		exec_builtin(t_sh_params **shell_params);
int		exec_void_cmd(t_ast *ast, t_sh_params **shell_params);
int		exec_cmd(char **args, t_list *lst_redir, t_sh_params **shell_params);
int		is_builtin(t_cmd *cmd);
int		exec_piped_builtin(t_ast *ast, t_sh_params **shell_params);
int		exec_pipeline(t_ast *ast, char **my_envp, t_sh_params **shell_params);
int		get_status(int pid);
void	exec_node(t_ast *ast_node, char **my_envp, t_sh_params **shell_params);
void	clear_and_close(t_sh_params **shell_params);
void	child_sigint_handler(int sig);

#endif