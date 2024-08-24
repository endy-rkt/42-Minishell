/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:46:52 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/24 15:51:14 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*cmd_initiate(t_token *tk)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;//0
	cmd->redir = NULL;//0
	cmd->assign = NULL;//0
	cmd->input = NULL;
	cmd->output = NULL;
	cmd->next = NULL;
	// cmd->test = ft_strdup(tk->value);
	return (cmd);
}

int	size_of_args(t_token *tk)
{
	int	size;

	size = 0;
	while (tk != NULL && tk->type == TK_PIPE)
	{
		if (tk->type == TK_WORD && tk->prev == NULL)
			break;
		else if (tk->type == TK_WORD && (tk->prev != NULL && is_redir(tk->prev)))
			break ;
		tk = tk->next;
	}
	while (tk != NULL && tk->type == TK_PIPE)
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

void	take_assign(t_token **tk, t_cmd **cmd)
{
	char	*value;

	if ((*tk)->type != TK_ASSIGN)
		return ;
	value = ft_strdup((*tk)->value);
	ft_lstadd_back(&((*cmd)->assign), ft_lstnew(value));
}

void	take_redir(t_token **tk, t_cmd **cmd)
{
	char	*tk_value;
	t_redir	*redir;

	if (!is_redir(*tk))
		return ;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;
	tk_value = (*tk)->value;
	redir->fd = ft_atoi(tk_value);
	redir->type = (*tk)->type;
	*tk = (*tk)->next;
	if (*tk)
		redir->file = ft_strdup((*tk)->value);
	ft_lstadd_back(&((*cmd)->redir), ft_lstnew(redir));
}

void	take_heredoc(t_token **tk, t_cmd **cmd)
{
	int		i;
	char	*tk_value;
	t_redir	*heredoc;

	if ((*tk)->type != TK_HEREDOC)
		return ;
	heredoc = malloc(sizeof(t_redir));
	if (!heredoc)
		return ;
	i = 0;
	tk_value = (*tk)->value;
	while (ft_isdigit(tk_value[i]))
		i++;
	heredoc->fd = ft_atoi(tk_value);
	heredoc->file = ft_strdup(tk_value + i);
	heredoc->type = TK_HEREDOC;
	ft_lstadd_back(&((*cmd)->redir), ft_lstnew(heredoc));
}

void	take_args(t_token **tk, t_cmd **cmd, int arg)
{
	char	**args;

	if ((*tk)->type == TK_ASSIGN && (*tk)->type != TK_WORD)
		return ;
	(*cmd)->args[arg] = ft_strdup((*tk)->value);
}

void	cmd_part1(t_token **tk, t_cmd **cmd)
{
	while ((*tk) != NULL && (*tk)->type == TK_PIPE)
	{
		if ((*tk)->type == TK_WORD && (*tk)->prev == NULL)
			break;
		else if ((*tk)->type == TK_WORD && ((*tk)->prev != NULL && is_redir((*tk)->prev)))
			break ;
		take_assign(tk, cmd);
		take_heredoc(tk, cmd);
		take_redir(tk, cmd);
		if (*tk)
			(*tk) = (*tk)->next;
	}
}

void	cmd_part2(t_token **tk, t_cmd **cmd)
{
	int	arg_nb;

	arg_nb = 0;
	while ((*tk) != NULL && (*tk)->type == TK_PIPE)
	{
		if (((*tk)->prev != NULL && !is_redir((*tk)->prev)) || (*tk)->prev == 	NULL)
		{
			take_args(tk, cmd, arg_nb);
			arg_nb++;
		}	
		take_heredoc(tk, cmd);
		take_redir(tk, cmd);
		*tk = (*tk)->next;
	}
	(*cmd)->args[arg_nb] = NULL;
}

void	cmd_addvalue(t_token *tk, t_cmd **cmd)
{
	int		args_size;
	char	**args;

	args_size = size_of_args(tk);
	args = malloc(sizeof(char *) * (args_size + 1));
	if (!args)
		return ;
	(*cmd)->args = args;
	cmd_part1(&tk, cmd);
	cmd_part2(&tk, cmd);
}

t_cmd	*cmd_create(t_token	*tk)
{
	t_cmd	*cmd;

	cmd	= cmd_initiate(tk);
	if (tk->type != TK_PIPE)
		cmd_addvalue(tk, &cmd);
	return (cmd);
}

t_cmd	*cmd_last(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->next)
			return (cmd_last(cmd->next));
		else
			return (cmd);
	}
	return (NULL);
}

void	cmd_addback(t_cmd **cmd, t_cmd *new_cmd)
{
	if (cmd)
	{
		if (*cmd)
			cmd_last(*cmd)->next = new_cmd;
		else
			*cmd = new_cmd;
	}
}

void	cmd_clear(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*next;

	if (cmd && *cmd)
	{
		tmp = *cmd;
		while (tmp)
		{
			next = tmp->next;
			//free(tmp);
			tmp = next;
		}
		*cmd = NULL;
	}
}


void	print_single_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		printf("----------------------------------------------------------------\n");
		printf("cmd:%s\n", cmd->test);
		// printf("args:%s\n");
		// printf("assign:%s\n");
		// printf("redir:%s\n");
		cmd = cmd->next;
	}
}
