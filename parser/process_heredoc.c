/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:10:34 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/18 14:11:48 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static volatile sig_atomic_t a = 0;

static void	sigint_handler(int sig)
{
    (void)sig;
	a = 130;
	close(STDIN_FILENO);
	ft_printf("");
}

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
		if (a == 130)
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
}

void	free_alloc(t_cmd **cmd, char *file, t_sh_params **shell_params, t_cmd **lst_cmd)
{
	if ((*shell_params)->my_envp)
		free_args(((*shell_params)->my_envp));	
	cmd_clear(lst_cmd);
	free_sh_params(shell_params);
	free(file);
}

void	update_status(int status, int pid, t_sh_params **shell_params)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	    status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
	    status = WTERMSIG(status) + 128;
	ft_printf("\033[2K\r");
	(*shell_params)->exit_status = status;
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
    if (pid == 0)
	{
		signal(SIGINT, sigint_handler);
		while (lst_redir != NULL)
    	{
			if (last_redir_in(lst_redir))
				stored_heredoc(cmd, lst_redir, file, shell_params);
			else
				tmp_heredoc(lst_redir, *shell_params);
			lst_redir = lst_redir->next;
    	}
		free_alloc(cmd, file, shell_params, lst_cmd);
		exit(a);
	}
	update_status(status, pid, shell_params);
}

t_list	*last_redirin(t_list *lst)
{
	t_list	*tmp;
	t_redir *r;

	if (last_redir_in(lst))
		return (lst);
	tmp = lst->next;
	while (tmp != NULL)
	{
		if (last_redir_in(tmp))
			break;
		r = lst->content;
		tmp = tmp->next;
	}
	r = tmp->content;
	return (tmp);
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
	last_lst = last_redirin((*cmd)->redir);
	lst_redir = &last_lst;
	redir = (t_redir**) &((*lst_redir)->content);
	free((*redir)->file);
	(*redir)->file = ft_strdup(file);
	(*redir)->type = TK_REDIR_IN;
	tmp_file = &((*shell_params)->tmp_file);
	tmp_str = ft_strdup(file);
	ft_lstadd_back(tmp_file, ft_lstnew(tmp_str));
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
