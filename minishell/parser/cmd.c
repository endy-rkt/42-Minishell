/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:13:08 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/14 10:32:22 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	cmd_part_1(t_token **tk, t_cmd **cmd)
{
	while ((*tk) != NULL && (*tk)->type != TK_PIPE)
	{
		if ((*tk)->type == TK_WORD && (*tk)->prev == NULL)
			break;
		else if ((*tk)->type == TK_WORD && ((*tk)->prev != NULL && !is_redir((*tk)->prev)))
			break ;
		take_assign(tk, cmd);
		take_heredoc(tk, cmd);
		take_redir(tk, cmd);
		if (*tk)
			(*tk) = (*tk)->next;
	}
}

static void	cmd_part_2(t_token **tk, t_cmd **cmd)
{
	int	arg_nb;
	int	have_taken_arg;

	arg_nb = 0;
	have_taken_arg = 0;
	while ((*tk) != NULL && (*tk)->type != TK_PIPE)
	{
		if (((*tk)->prev != NULL && !is_redir((*tk)->prev)) || (*tk)->prev == NULL)
		{
			have_taken_arg = take_args(tk, cmd, arg_nb);
			if (have_taken_arg)
				arg_nb++;
		}	
		take_heredoc(tk, cmd);
		take_redir(tk, cmd);
		*tk = (*tk)->next;
	}
	(*cmd)->args[arg_nb] = NULL;
}

static void	cmd_addvalue(t_token **tk, t_cmd **cmd)
{
	int		args_size;
	char	**args;

	args_size = size_of_args(*tk);
	args = malloc(sizeof(char *) * (args_size + 1));
	if (!args)
		return ;
	(*cmd)->args = args;
	(*cmd)->args[0] = NULL;
	cmd_part_1(tk, cmd);
	cmd_part_2(tk, cmd);
}

static t_cmd	*create_one_cmd(t_token	**tk)
{
	t_cmd	*cmd;

	cmd	= cmd_initiate();
	if ((*tk)->type != TK_PIPE)
		cmd_addvalue(tk, &cmd);
	return (cmd);
}

t_cmd	*create_cmd_list(t_token *tk, t_sh_params **shell_params)
{
	t_cmd	*cmd;
	t_cmd	*new_cmd;

	cmd = NULL;
	while (tk)
	{
		if (tk->type != TK_PIPE)
		{
			new_cmd = create_one_cmd(&tk);
			while (tk != NULL && tk->type != TK_PIPE)
				tk = tk->next;
		}
		else
		{
			new_cmd = create_one_cmd(&tk);
			tk = tk->next;
		}
		cmd_addback(&cmd, new_cmd);
	}
	process_heredoc(&cmd, shell_params);
	return (cmd);
}
