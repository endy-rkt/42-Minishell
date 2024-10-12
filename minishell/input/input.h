/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:29:42 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/12 13:14:13 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H

# include "../header.h"
# include "../builtin/buildin.h"

int	process_loop(int (*run_shell)(char *, char **, int), char **envp);

#endif