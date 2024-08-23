/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 07:20:23 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/23 10:22:25 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clear_args(char	***args)
{
	int	i;

	i = 0;
	while (*args[i])
	{
		free(*args[i]);
		i++;
	}
	free(*args);
}

void	clear_redir(void *redir)
{
	t_redir	*tmp;

	tmp = (t_redir *)redir;
	free(tmp->str);
	free(tmp);
}

void	clear_assign(void *assign)
{
	char	*str;

	str = (char *)assign;
	free(str);
}

t_redir	*create_redir(char *str, token_type type, int is_last)
{
	t_redir	*redir;

	redir = malloc(sizeof(redir));
	if (!redir)
		return (NULL);
	redir->is_last = is_last;
	redir->str = str;
	redir->type = type;
	return (redir);
}
