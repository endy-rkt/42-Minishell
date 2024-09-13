/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:10:34 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/13 11:14:47 by trazanad         ###   ########.fr       */
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
		if (strcmp(input, delimiter) == 0)
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

static void	stored_heredoc(t_cmd **cmd, t_list *lst_redir, char file, t_sh_params **shell_params)
{
	int		fd;
	char	*value;
    t_redir *redir;

    redir = lst_redir->content;
    if (redir->type != TK_HEREDOC)
        return ;
	value = heredoc_value(redir, *shell_params);
	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (value != NULL)
		write(fd, value, ft_strlen(value));
	if (value != NULL)
		free(value);
	close(fd);
	change_heredoc(cmd, file, shell_params);
}

static void	handle_heredoc(t_cmd **cmd, char *file, t_sh_params **shell_params)
{
    t_list	*lst_redir;

    lst_redir = (*cmd)->redir;
    if (lst_redir == NULL)
        return ;
    while (lst_redir != NULL)
    {
		if (last_redir_in(lst_redir))
		    stored_heredoc(cmd, lst_redir, file, shell_params);
		else
        	tmp_heredoc(lst_redir, *shell_params);
        lst_redir = lst_redir->next;
    }
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
        handle_heredoc(&tmp, file, shell_params);
        free(file);
        i++;
        tmp = tmp->next;
    }
}
