/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:10:34 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/15 16:45:38 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*heredoc_value(t_redir *rd, t_sh_params *shell_params)
{
	char	*value;
	char	*input;
	char	*delimiter;

	value = NULL;
	delimiter = take_delim(rd);
	while (1)
	{
		input = NULL;
		ft_printf("heredoc>");
		input = get_next_line(0);
		if (input != NULL && ft_strcmp(input, delimiter) == 0)
			break ;
		input = hdoc_new_val(rd, input, shell_params);
		value = ft_strjoin(value, input);
		free(input);
	}
	free(delimiter);
	free(input);
	return (value);
}

static void	tmp_heredoc(t_list *lst_redir, t_sh_params *shell_params)
{
	char	*value;
    t_redir *redir;

    redir = lst_redir->content;
    if (redir->type != TK_HEREDOC)
        return ;
	value = heredoc_value(redir, shell_params);
	if (value != NULL)
		free(value);
}

static void	stored_heredoc(t_cmd **cmd, t_list *lst_redir, char *file, t_sh_params **shell_params)
{
	int		fd;
	char	*value;
    t_redir *redir;

    redir = lst_redir->content;
    if (redir->type != TK_HEREDOC)
        return ;
	value = heredoc_value(redir, *shell_params);
	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (value != NULL)
		write(fd, value, ft_strlen(value));
	if (value != NULL)
		free(value);
	close(fd);
	//change_heredoc(&lst_redir, file, shell_params);
}

static void	handle_heredoc(t_cmd **cmd, char *file, t_sh_params **shell_params, char **input)
{
	int		pid;
    t_list	*lst_redir;
	int		status;

	status = 0;
    lst_redir = (*cmd)->redir;
    if (lst_redir == NULL)
        return ;
	pid = fork();
    if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		while (lst_redir != NULL)
    	{
			if (last_redir_in(lst_redir))
				stored_heredoc(cmd, lst_redir, file, shell_params);
			else
				tmp_heredoc(lst_redir, *shell_params);
			lst_redir = lst_redir->next;
    	}
		if ((*shell_params)->my_envp)
		free_args(((*shell_params)->my_envp));
		free_sh_params(shell_params);
		cmd_clear(cmd);
		free(file);
		free(*input);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	    status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
	    status = WTERMSIG(status) + 18;
	ft_printf("\033[2K\r");
	(*shell_params)->exit_status = status;
}

void	add_tmp_file(char *file, t_sh_params **shell_params, t_cmd **cmd)
{
	char	*tmp_str;
	t_list	*last_lst;
	t_list	**lst_redir;
	t_redir **redir;
	t_list	**tmp_file;

	if (access(file, F_OK) != 0)
		return ;
	last_lst = ft_lstlast((*cmd)->redir);
	lst_redir = &last_lst;
	redir = (t_redir**) &((*lst_redir)->content);
	free((*redir)->file);
	(*redir)->file = ft_strdup(file);
	(*redir)->type = TK_REDIR_IN;
	tmp_file = &((*shell_params)->tmp_file);
	tmp_str = ft_strdup(file);
	ft_lstadd_back(tmp_file, ft_lstnew(tmp_str));
}

void    process_heredoc(t_cmd **cmd, t_sh_params **shell_params, char **input)
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
        handle_heredoc(&tmp, file, shell_params, input);
		add_tmp_file(file, shell_params, &tmp);
        free(file);
        i++;
        tmp = tmp->next;
    }
}
