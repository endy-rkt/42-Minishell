/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:52:07 by trazanad          #+#    #+#             */
/*   Updated: 2024/07/17 10:47:03 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

int	main(void)
{
	int	fd[2];
	if (pipe(fd) < 0)
		exit(EXIT_FAILURE);
	int pid1 = fork();
	if (pid1 == -1)
		exit(EXIT_FAILURE);
	if (pid1 == 0)
	{
		//ping
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c" , "3", "google.com", NULL);
	}
	else
	{
		//grep
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execlp("grep", "grep", "rtt", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	return (0);
}
