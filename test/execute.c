/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:36:14 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/21 14:44:17 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	main(int ac, char **av)
{
	char **arg;

	arg=malloc(sizeof(char*)*4);
	// printf("--%s--\n",arg[0]);
	// printf("--%s--\n",arg[1]);
	// printf("--%s--\n",arg[2]);
	// printf("--%s--\n",arg[3]);
	arg[0] = strdup("awk");
	arg[1] =strdup("{print $1}");
	arg[2] =strdup("a");
	arg[3] =NULL;
	// printf("--%s--\n",arg[0]);
	// printf("--%s--\n",arg[1]);
	// printf("--%s--\n",arg[2]);
	// printf("--%s--\n",arg[3]);
	execve("/bin/awk", arg, NULL);
}