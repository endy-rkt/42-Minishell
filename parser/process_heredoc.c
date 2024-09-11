/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:47:09 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 15:51:49 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	launch_heredoc(t_redir *rd)
{
	int		i;
	char	*delimiter;
	char	*input;

	i = 0;
	delimiter = rd->file;
	while (delimiter[i] == '<' || ft_isdigit(delimiter[i]))
		i++;
	delimiter = delimiter + i;
	// printf("delimiter:%s\n", delimiter);s
	while (1)
	{
		input = NULL;
		ft_printf("heredoc>");
		input = get_next_line(0);
		if (ft_strncmp(input, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		free(input);
	}
}

int	handle_heredoc(t_redir *rd, char *file)
{
	int		i;
	char	*delimiter;
	char	*input;
	char	*value;
	int		fd;

	i = 0;
	delimiter = rd->file;
	while (delimiter[i] == '<' || ft_isdigit(delimiter[i]))
		i++;
	delimiter = delimiter + i;
	fd = open(file, O_RDWR | O_TRUNC |O_CREAT, 0777);
	value = ft_strdup("");
	while (1)
	{
		input = NULL;
		ft_printf("heredoc>");
		input = get_next_line(0);
		if (ft_strncmp(input, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		value = ft_strjoin(value, input);
		free(input);
	}
	write(fd, value, ft_strlen(value));
	free(value);
	close(fd);
	return (fd);
}

void    process_heredoc_cmd(t_cmd **cmd, char *file)
{
    t_list  *lst_redir;
    t_list  *last_redir;
    t_redir *rd;
    t_redir *new_redir;

    lst_redir = (*cmd)->redir_in;
    if (lst_redir == NULL)
        return ;
    last_redir = ft_lstlast(lst_redir);
    while (lst_redir != last_redir)
    {
        rd = lst_redir->content;
        if (rd->type == TK_HEREDOC)
            launch_heredoc(rd);
        lst_redir = lst_redir->next;
    }
    rd = lst_redir->content;
    if (rd->type == TK_HEREDOC)
    {
        handle_heredoc(rd, file);
        new_redir = malloc(sizeof(t_redir));
	    if (!new_redir)
	    	return ;
	    new_redir->fd = STDIN_FILENO;
	    new_redir->type = TK_REDIR_IN;
	    new_redir->file = ft_strdup(file);
        ft_lstadd_back(&((*cmd)->redir_in), ft_lstnew(new_redir));
    }
}

void    process_heredoc(t_cmd **cmd)
{
    int     i;
    char    *file;
	char	*str;
    t_cmd *tmp;

    i = 0;
    tmp = *cmd;
	str = NULL;
    file = ft_strdup(".tmp");
    while (tmp)
    {
		str = ft_itoa(i);
        file = ft_strjoin(file, str);
        process_heredoc_cmd(&tmp, file);
        i++;
        tmp = tmp->next;
		free(str);
    }
    free(file);
}
