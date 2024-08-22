/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:09:16 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/22 08:53:32 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_cmd(t_token *tk)
{
	t_cmd	*cmd;
	t_token	*tmp;

	cmd = create_cmd(tk);
	tmp = tk->next;
	while (tmp)
	{
		if (tmp->type != TK_PIPE)
			cmd_add_back(&cmd, create_cmd(tmp));
		tmp = tmp->next;
	}
}
