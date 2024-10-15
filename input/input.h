/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:29:42 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/14 10:58:57 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H

# include "../header.h"
# include "../minishell.h"

int	process_loop(int (*run_shell)(char *, char ***, int), char **envp);

#endif