/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:10:34 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 17:00:57 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*heredoc_value(t_redir *rd, t_sh_params *sh_params)
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
		input = hdoc_new_val(rd, input, sh_params);
		value = ft_strjoin(value, input);
		free(input);
	}
	free(delimiter);
	free(input);
	return (value);
}

static void	tmp_heredoc(t_list *lst_redir, t_sh_params *sh_params)
{
	char	*value;
    t_redir *redir;

    redir = lst_redir->content;
    if (redir->type != TK_HEREDOC)
        return ;
	value = heredoc_value(redir, sh_params);
	if (value != NULL)
		free(value);
}

static void	stored_heredoc(t_cmd **cmd, t_list *lst_redir, char file, t_sh_params **sh_params)
{
	int		fd;
	char	*value;
    t_redir *redir;

    redir = lst_redir->content;
    if (redir->type != TK_HEREDOC)
        return ;
	value = heredoc_value(redir, *sh_params);
	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (value != NULL)
		write(fd, value, ft_strlen(value));
	if (value != NULL)
		free(value);
	close(fd);
	change_heredoc(cmd, file, sh_params);
}

static void	handle_heredoc(t_cmd **cmd, char *file, t_sh_params **sh_params)
{
    t_list	*last_redir;
    t_list	*lst_redir;

    lst_redir = (*cmd)->redir_in;
    if (lst_redir == NULL)
        return ;
    last_redir = ft_lstlast(lst_redir);
    while (lst_redir != last_redir)
    {
        tmp_heredoc(lst_redir, *sh_params);
        lst_redir = lst_redir->next;
    }
    stored_heredoc(cmd, lst_redir, file, sh_params);
}

void    process_heredoc(t_cmd **cmd, t_sh_params **sh_params)
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
        handle_heredoc(&tmp, file, sh_params);
        free(file);
        i++;
        tmp = tmp->next;
    }
}