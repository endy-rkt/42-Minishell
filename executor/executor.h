/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 14:57:22 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/02 15:35:32 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H

# define EXECUTOR_H

# include "../parser/parser.h"

int		execute_cmd(t_cmd *cmd);
void	execute_ast(t_ast *ast);

#endif