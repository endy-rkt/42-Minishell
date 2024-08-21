/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:55:40 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/21 16:51:26 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_assign	*create_assign(char *word)
{
	int			i;
	char		*key;
	t_assign	*assign;

	assign = malloc(sizeof(t_assign));
	if (!assign)
		return (NULL);
	key = strdup(word);
	i = 0;
	while (key[i] != '=')
		i++;
	key[i] = '\0';
	assign->key = key;
	assign->value = strdup(word + i + 1);
	assign->next = NULL;
	return (assign);
}

t_assign	*assign_last(t_assign *assign)
{
	if (assign)
	{
		if (assign->next)
			return (assign_last(assign->next));
		else
			return (assign);
	}
	return (NULL);
}

void	assign_add_back(t_assign **assign, t_assign *new)
{
	if (assign)
	{
		if (*assign)
			assign_last(*assign)->next = new;
		else
			*assign = new;
	}
}

void	assign_clear(t_assign **assign)
{
	t_assign	*tmp;
	t_assign	*next;

	if (assign)
	{
		if (*assign)
		{
			tmp = *assign;
			while (tmp)
			{
				next = tmp->next;
				if (tmp->key)
					free(tmp->key);
				if (tmp->value)
					free(tmp->value);
				free(tmp);
				tmp = next;
			}
		}
	}
}

// int main(int argc, char *argv[])
// {
// 	t_assign	*assign;

// 	assign = create_assign(argv[1]);
// 	printf("key=%s value=%s\n", assign->key, assign->value);
// }