/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:10:34 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/19 14:17:51 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static volatile sig_atomic_t g_sig = 0;

static void	sigint_handler(int sig)
{
    (void)sig;
	g_sig = 130;
	close(STDIN_FILENO);
}

char	*heredoc_value(t_redir *rd, t_sh_params *shell_params)
{
	static char	*value = NULL;
	static char	*input = NULL;
	char		*delimiter;

	delimiter = take_delim(rd);
	while (1)
	{
		ft_printf("heredoc>");
		input = get_next_line(0);
		if (input != NULL && ft_strcmp(input, delimiter) == 0)
			break ;
		if (g_sig == 130)
		{
			free(input);
			break ;
		}
		input = hdoc_new_val(rd, input, shell_params);
		value = ft_strjoin(value, input);
		free(input);
	}
	free(delimiter);
	free(input);
	return (value);
}

static void	manage_heredoc(t_list	*lst_redir, t_cmd **cmd, char *file, t_sh_params **shell_params)
{
	if (last_redir_in(lst_redir))
		stored_heredoc(cmd, lst_redir, file, shell_params);
	else
		tmp_heredoc(lst_redir, *shell_params);
}

static void	handle_heredoc(t_cmd **cmd, char *file, t_sh_params **shell_params, t_cmd **lst_cmd)
{
	int		pid;
    t_list	*lst_redir;
	int		status;

	status = 0;
    lst_redir = (*cmd)->redir;
    if (lst_redir == NULL)
        return ;
	pid = fork();
	signal(SIGINT, SIG_IGN);
    if (pid == 0)
	{
		signal(SIGINT, sigint_handler);
		while (lst_redir != NULL)
    	{
			if (g_sig)
				break ; 
			manage_heredoc(lst_redir, cmd, file, shell_params);
			lst_redir = lst_redir->next;
    	}
		clean_alloc(cmd, file, shell_params, lst_cmd);
		exit(g_sig);
	}
	hdoc_status(status, pid, shell_params);
}

void    process_heredoc(t_cmd **cmd, t_sh_params **shell_params)
{
    int     i;
    char    *str;
    char    *file;
    t_cmd   *tmp;

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
