/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:16:45 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/12 10:20:27 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int main(int argc , char **argv)
{
	int fd;
	char 	str[6];

	fd = open(argv[1], O_WRONLY | O_CREAT, 0777);
	write(fd, "test", 5);
	read(fd, str, 5);
	printf("fd=%d,text=%s\n", fd ,str);
	close(fd);
	return (0);
}