/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:46:52 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/25 00:22:27 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	*cmd_initiate()
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
	return (cmd);
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

int	take_assign(t_token **tk, t_cmd **cmd)
{
	char	*value;

	if ((*tk)->type != TK_ASSIGN)
		return (0);
	value = ft_strdup((*tk)->value);
	ft_lstadd_back(&((*cmd)->assign), ft_lstnew(value));
	return (1);
}

int	take_redir(t_token **tk, t_cmd **cmd)
{
	char	*tk_value;
	t_redir	*redir;

	if (!is_redir(*tk))
		return (0);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (0);
	tk_value = (*tk)->value;
	redir->fd = ft_atoi(tk_value);
	redir->type = (*tk)->type;
	*tk = (*tk)->next;
	if ((*tk) != NULL && ((*tk)->type == TK_WORD || (*tk)->type == TK_ASSIGN))
		redir->file = ft_strdup((*tk)->value);
	ft_lstadd_back(&((*cmd)->redir), ft_lstnew(redir));
	return (1);
}

int	take_heredoc(t_token **tk, t_cmd **cmd)
{
	int		i;
	char	*tk_value;
	t_redir	*heredoc;

	if ((*tk)->type != TK_HEREDOC)
		return (0);
	heredoc = malloc(sizeof(t_redir));
	if (!heredoc)
		return (0);
	i = 0;
	tk_value = (*tk)->value;
	while (ft_isdigit(tk_value[i]) || tk_value[i] == '<')
		i++;
	heredoc->fd = ft_atoi(tk_value);
	heredoc->file = ft_strdup(tk_value + i);
	heredoc->type = TK_HEREDOC;
	ft_lstadd_back(&((*cmd)->redir), ft_lstnew(heredoc));
	return (1);
}

int	take_args(t_token **tk, t_cmd **cmd, int arg)
{
	char	**args;

	if ((*tk)->type != TK_ASSIGN && (*tk)->type != TK_WORD)
		return (0);
	(*cmd)->args[arg] = ft_strdup((*tk)->value);
	return (1);
}

void	cmd_part1(t_token **tk, t_cmd **cmd)
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

void	cmd_part2(t_token **tk, t_cmd **cmd)
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

void	cmd_addvalue(t_token **tk, t_cmd **cmd)
{
	int		args_size;
	char	**args;

	args_size = size_of_args(*tk);
	args = malloc(sizeof(char *) * (args_size + 1));
	if (!args)
		return ;
	(*cmd)->args = args;
	cmd_part1(tk, cmd);
	cmd_part2(tk, cmd);
}

t_cmd	*cmd_create(t_token	**tk)
{
	t_cmd	*cmd;

	cmd	= cmd_initiate();
	if ((*tk)->type != TK_PIPE)
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
		if (!cmd->args && !cmd->assign && !cmd->redir)
		{
			printf("pipe\n");
		}
		if (cmd->args)
		{
			int i =0;
			printf("args:\t");
			while (cmd->args[i])
			{
				printf("{%s}\t", cmd->args[i]);
				i++;
			}
			printf("\n");
		}
		if (cmd->assign)
		{
			t_list *assign = cmd->assign;
			printf("assign:\t");
			while (assign)
			{
				printf("{%s}\t", (char*)assign->content);
				assign = assign->next;
			}
			printf("\n");
		}
		if (cmd->redir)
		{
			t_list *redir= cmd->redir;
			t_redir *tmp;
			printf("redir:\t");
			while (redir)
			{
				tmp = (t_redir *)redir->content;
				printf("{%s}{%d}{%d}\t", tmp->file, tmp->fd, tmp->type);
				redir = redir->next;
			}
			printf("\n");
		}
		// printf("args:%s\n");
		// printf("assign:%s\n");
		// printf("redir:%s\n");
		cmd = cmd->next;
	}
}