/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:30:37 by ferafano          #+#    #+#             */
/*   Updated: 2024/11/03 14:11:35 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int	ft_env(char **copy_env, char **argv, int fd)
{
	int	i;

	i = 0;
	if (argv[1] != NULL)
	{
		write(2, "env: too many arguments\n", 24);
		return (1);
	}
	while (copy_env[i])
	{
		if (ft_strchr(copy_env[i], '='))
		{
			ft_putstr_fd(copy_env[i], fd);
			ft_putchar_fd('\n', fd);
		}
		i++;
	}
	return (0);
}

void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	bubble_sort(char **array, int length)
{
	int	i;
	int	j;
	int	swapped;

	i = 0;
	while (i < length - 1)
	{
		swapped = 0;
		j = 0;
		while (j < length - i - 1)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0)
			{
				swap(&array[j], &array[j + 1]);
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
}

void	cond_loop(t_print_exp *exp, int *j, int fd)
{
	while (exp->temp_env[exp->temp_i][*j])
	{
		if (exp->temp_env[exp->temp_i][*j] == '"')
			ft_putstr_fd("\\", fd);
		ft_putchar_fd(exp->temp_env[exp->temp_i][*j], fd);
		(*j)++;
	}
}
