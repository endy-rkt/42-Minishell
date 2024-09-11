/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:36:46 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 17:01:07 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_args(char **args)
{
	int	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static void	free_redir(t_redir **redir)
{
	if (redir == NULL)
		return ;
	if (*redir == NULL)
		return ;
	if ((*redir)->file != NULL)
		free((*redir)->file);
}

static void	free_assign(char *value)
{
	if (value != NULL)
		free(value);
}

void	free_one_cmd(t_cmd **cmd)
{
	free_args((*cmd)->args);
	ft_lstclear(&((*cmd)->assign), free_assign);
	ft_lstclear(&((*cmd)->redir_in), free_redir);
	ft_lstclear(&((*cmd)->redir_out), free_redir);
	(*cmd)->args = NULL;
	(*cmd)->assign = NULL;
	(*cmd)->redir_in = NULL;
	(*cmd)->redir_out = NULL;
}

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
