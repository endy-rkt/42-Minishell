/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:03:37 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/16 13:02:16 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef executor_H

# define executor_H

# include "../header.h"

# include "../parser/parser.h"

void	execute(t_sh_params **shell_params);
char	*get_path(char **args, char **my_envp, int *err_status);

#endif