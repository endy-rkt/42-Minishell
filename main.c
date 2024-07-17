/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:52:07 by trazanad          #+#    #+#             */
/*   Updated: 2024/07/17 15:42:52 by trazanad         ###   ########.fr       */
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
#define PROCESS_NB 3

int	main(void)
{
	int	pipes[PROCESS_NB + 1][2];
	for (int i = 0; i < PROCESS_NB; i++)
	{
		if (pipe(pipes[i]) == -1)
			exit(EXIT_FAILURE);
	}
	int	pids[PROCESS_NB];
	for (int i = 0; i < PROCESS_NB; i++)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			exit(EXIT_FAILURE);
		if (pids[i] == 0)
		{
			
			break;
		}
	}
	for (int i = 0; i < PROCESS_NB; i++)
		wait(NULL);
	return (0);
}
