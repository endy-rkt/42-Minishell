/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_operation_utils.c.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:36:46 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/19 11:01:34 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	size_of_args(t_token *tk)
{
	int	size;

	size = 0;
	while (tk != NULL && tk->type != TK_PIPE)
	{
		if (tk->type == TK_WORD && tk->prev == NULL)
			break;
		else if (tk->type == TK_WORD && (tk->prev != NULL && !is_redir(tk->prev)))
			break ;
		tk = tk->next;
	}
	while (tk != NULL && tk->type != TK_PIPE)
	{
		if (tk->type == TK_WORD || tk->type == TK_ASSIGN)
		{
			if (tk->prev == NULL && tk->type == TK_WORD)
				size++;
			else if (tk->prev != NULL && !is_redir(tk->prev))
				size++;
		}
		tk = tk->next;
	}
	return (size);
}

void	free_args(char **args)
{
	int	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = NULL;
}

void	free_redir(void *redir)
{
	t_redir	*tmp_redir;

	tmp_redir = (t_redir *) redir;
	if (tmp_redir == NULL)
		return ;
	if (tmp_redir == NULL)
		return ;
	if (tmp_redir->file != NULL)
		free(tmp_redir->file);
	free(tmp_redir);
}

void	free_assign(void *value)
{
	if (value != NULL)
		free(value);
}

void	free_one_cmd(t_cmd **cmd)
{
	if (cmd == NULL || *cmd == NULL)
		return ;
	if ((*cmd)->args)
		free_args((*cmd)->args);
	if ((*cmd)->assign)
		ft_lstclear(&((*cmd)->assign), free_assign);
	if ((*cmd)->redir)
		ft_lstclear(&((*cmd)->redir), free_redir);
	(*cmd)->args = NULL;
	(*cmd)->assign = NULL;
	(*cmd)->redir = NULL;
	free(*cmd);
	*cmd = NULL;
}

