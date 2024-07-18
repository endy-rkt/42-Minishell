/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:52:07 by trazanad          #+#    #+#             */
/*   Updated: 2024/07/18 11:11:07 by trazanad         ###   ########.fr       */
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
#include <pthread.h>

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
	int	index = *(int *)arg;
	printf("%d ", primes[index]);
	free(arg);
}

int	main(void)
{
	pthread_t	th[10];

	for (int i = 0; i < 10; i++)
	{
		int	*tmp = malloc(sizeof(int));
		*tmp = i;
		if (pthread_create(th + i, NULL, &routine, tmp) != 0)
			exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 10; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			exit(EXIT_FAILURE);
	}
	return (0);
}
