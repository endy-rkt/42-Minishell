/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:13:33 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/12 12:14:13 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	last_redir_in(t_list *lst_redir)
{
	t_list	*tmp;
	t_redir *redir;

	tmp = lst_redir->next;
	while (tmp)
	{
		redir = tmp->content;
		if (redir->type == TK_HEREDOC || redir->type == TK_REDIR_IN || redir->type == TK_REDIR_IN2)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	last_redir_out(t_list *lst_redir)
{
	t_list	*tmp;
	t_redir *redir;

	tmp = lst_redir->next;
	while (tmp)
	{
		redir = tmp->content;
		if (redir->type == TK_REDIR_OUT || redir->type == TK_REDIR_APPEND)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
