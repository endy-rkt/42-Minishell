/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:03:37 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/16 12:47:39 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef executor_H

# define executor_H

# include "../header.h"

# include "../parser/parser.h"

# include "../builtin/buildin.h"

void	execute(t_sh_params **shell_params);
int 	exec_pipeline(t_ast *ast, char **my_envp, t_sh_params **shell_params);
char	*get_path(char **args, char **my_envp, int *err_status);
void	exec_node(t_ast *ast_node, char **my_envp, t_sh_params **shell_params);
void	spwan_child(t_ast *ast, char **my_envp, t_sh_params **shell_params);
int		change_redir(t_list *lst_redir, int stdin, int stdout);
int		get_status(int pid);
int		is_builtin(t_cmd *cmd);

#endif