/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:17:47 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 17:25:52 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	handle_stdin(t_cmd *cmd)
{
	
}

int	handle_stdout(t_cmd *cmd)
{
	int		fd;
	t_redir	*redir;
	t_list	*lst_redir;
	t_list	*last_redir;

	lst_redir = cmd->redir_out;
	if (lst_redir == NULL)
		return (STDOUT_FILENO);
	last_redir = ft_lstlast(lst_redir);
	while (lst_redir != last_redir)
	{
		redir = lst_redir->content;
		fd = open(redir->file, O_WRONLY | O_CREAT, 0777);
		close(fd);
		lst_redir = lst_redir->next;
	}
	redir = lst_redir->content;
	if (redir->type == TK_REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else
		fd = open(redir->file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	return (fd);
}
