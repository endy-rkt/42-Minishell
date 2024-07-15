/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:52:07 by trazanad          #+#    #+#             */
/*   Updated: 2024/07/15 15:27:41 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

int	main(void)
{
	if (mkfifo("myfifo1", 0777) == -1)
	{
		if (errno != EEXIST)
		{
			printf("Could not create fifo file\n");
			exit(EXIT_FAILURE);
		}
	}

	int	fd = open("myfifo1", O_WRONLY);
	int	x = 97;
	write(fd, &x, sizeof(x));
	close(fd);
	return (0);
}
