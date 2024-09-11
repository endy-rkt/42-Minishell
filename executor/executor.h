/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:57:22 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 10:47:43 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H

# define EXECUTOR_H

# include "../parser/parser.h"

int	    execute_cmd(t_ast *ast, int fd_0, int fd_1);
int 	execute_pipe(t_ast *ast);
void	execute_ast(t_ast *ast);

#endif