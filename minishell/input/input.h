/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:29:42 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 13:38:04 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H

# include "../header.h"

int	process_loop(int (*run_shell)(char *, char **), char **envp);

#endif