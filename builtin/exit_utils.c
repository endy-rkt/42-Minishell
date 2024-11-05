/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:19:02 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/04 13:43:46 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

long	ft_atol(char *nptr)
{
	int		paire;
	long	nb;

	nb = 0;
	paire = nb;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	while (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			paire++;
		nptr++;
		if (*nptr == '+' || *nptr == '-')
			return (0);
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		nb *= 10;
		nb += *nptr - 48;
		nptr++;
	}
	if (!(paire % 2))
		return (nb);
	return (-nb);
}

void	exit_trim(char **argv)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "") || !ft_is_blank(argv[i]))
		{
			tmp = ft_retire_space(argv[i]);
			free(argv[i]);
			argv[i] = tmp;
		}
		i++;
	}
}
