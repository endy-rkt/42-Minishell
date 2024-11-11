/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:10:34 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/11 09:13:32 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static volatile sig_atomic_t	g_sig = 0;

static void	sigint_handler(int sig)
{
	(void)sig;
	g_sig = 130;
	close(STDIN_FILENO);
}

static int	break_loop(char *input, char *delimiter)
{
	if (input == NULL)
	{
		if (g_sig == 130)
			ft_putstr_fd("\n", 2);
		else
			ft_putstr_fd("\nminishell: heredoc warning\n", 2);
		return (1);
	}
	if (input != NULL && ft_strcmp(input, delimiter) == 0)
		return (1);
	if (g_sig == 130)
		return (1);
	return (0);
}

char	*heredoc_value(t_redir *rd, t_sh_params *shell_params)
{
	char	*value;
	char	*input;
	char	*delimiter;
	char	*tmp_input;

	delimiter = take_delim(rd);
	value = NULL;
	input = NULL;
	tmp_input = NULL;
	while (1)
	{
		input = readline("heredoc> ");
		if (break_loop(input, delimiter))
			break ;
		input = hdoc_new_val(rd, input, shell_params);
		value = ft_strjoin(value, input);
		value = ft_strjoin(value, "\n");
		free(input);
		input = NULL;
	}
	free(delimiter);
	return (value);
}

static void	handle_heredoc(t_cmd **cmd, char *file, t_sh_params **shell_params,
		t_cmd **lst_cmd)
{
	int		pid;
	t_list	*lst_redir;

	lst_redir = (*cmd)->redir;
	if (lst_redir == NULL)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		while (lst_redir != NULL)
		{
			if (g_sig)
				break ;
			manage_heredoc(lst_redir, file, shell_params);
			lst_redir = lst_redir->next;
		}
		clean_alloc(file, shell_params, lst_cmd);
		exit(g_sig);
	}
	hdoc_status(pid, shell_params);
}

void	process_heredoc(t_cmd **cmd, t_sh_params **shell_params)
{
	int		i;
	char	*str;
	char	*file;
	t_cmd	*tmp;

	i = 0;
	tmp = *cmd;
	while (tmp)
	{
		str = ft_itoa(i);
		file = ft_strdup(".tmp");
		file = ft_strjoin(file, str);
		free(str);
		handle_heredoc(&tmp, file, shell_params, cmd);
		add_tmp_file(file, shell_params, &tmp);
		free(file);
		if ((*shell_params)->exit_status)
			break ;
		i++;
		tmp = tmp->next;
	}
}
