/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:52:07 by trazanad          #+#    #+#             */
/*   Updated: 2024/07/16 15:23:46 by trazanad         ###   ########.fr       */
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
	int pid = fork();

	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		int	fd = open("ping_result.txt", O_WRONLY | O_CREAT, 0777);
		if (fd == -1)
			exit(EXIT_FAILURE);
		printf("The fd to pingResult: %d\n", fd);
		int fd0 = dup2(fd, STDOUT_FILENO);
		close(fd);
		char	*arg[] = {
			"/usr/bin/ping",
			"-c",
			"3",
			"google.com",
			NULL
		};
		int err = execv("/usr/bin/ping", arg);
		if (err == -1)
		{
			printf("Error when executing command\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int	wait_status;
		wait(&wait_status);
		if (WIFEXITED(wait_status))
		{
			int status_code = WEXITSTATUS(wait_status);
			if (status_code == 0)
				printf("Success\n");
			else
				printf("Failure with status code: %d\n", status_code);
		}
	}
	return (0);
}
