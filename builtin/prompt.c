/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:13:08 by ferafano          #+#    #+#             */
/*   Updated: 2024/11/03 14:13:59 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int	ft_pwd(int fd)
{
	char	pwd[1024];

	getcwd(pwd, sizeof(pwd));
	ft_putstr_fd(pwd, fd);
	write(1, "\n", 1);
	return (0);
}
