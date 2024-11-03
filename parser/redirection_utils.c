/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:08:02 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/03 15:54:52 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*last_redirin(t_list *lst)
{
	t_list	*tmp;

	if (last_redir_in(lst))
		return (lst);
	tmp = lst->next;
	while (tmp != NULL)
	{
		if (last_redir_in(tmp))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	invalid_fd(int fd, char *file)
{
	if (fd != -1)
		return ;
	if (access(file, F_OK))
		print_error(file, " No such file or directory\n");
	else if (access(file, R_OK | W_OK))
		print_error(file, " Permission denied\n");
	close(fd);
}

void	add_tmp_file(char *file, t_sh_params **shell_params, t_cmd **cmd)
{
	char	*tmp_str;
	t_list	*last_lst;
	t_list	**lst_redir;
	t_redir	**redir;
	t_list	**tmp_file;

	if (access(file, F_OK) != 0)
		return ;
	last_lst = last_redirin((*cmd)->redir);
	lst_redir = &last_lst;
	redir = (t_redir **)&((*lst_redir)->content);
	free((*redir)->file);
	(*redir)->file = ft_strdup(file);
	(*redir)->type = TK_REDIR_IN;
	tmp_file = &((*shell_params)->tmp_file);
	tmp_str = ft_strdup(file);
	ft_lstadd_back(tmp_file, ft_lstnew(tmp_str));
}

void	tmp_heredoc(t_list *lst_redir, t_sh_params *shell_params)
{
	char	*value;
	t_redir	*redir;

	value = NULL;
	redir = lst_redir->content;
	if (redir->type != TK_HEREDOC)
		return ;
	value = heredoc_value(redir, shell_params);
	if (value != NULL)
		free(value);
}

void	stored_heredoc(t_list *lst_redir, char *file,
		t_sh_params **shell_params)
{
	int		fd;
	char	*value;
	t_redir	*redir;

	redir = lst_redir->content;
	value = NULL;
	if (redir->type != TK_HEREDOC)
		return ;
	value = heredoc_value(redir, *shell_params);
	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
		return ;
	if (value != NULL)
		write(fd, value, ft_strlen(value));
	if (value != NULL)
		free(value);
	close(fd);
}
