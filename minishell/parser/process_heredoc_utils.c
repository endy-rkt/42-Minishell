/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:35:14 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/12 12:14:08 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	format_delimiter(char *value, char **new_value, int i, int j)
{
	char	tmp;

	tmp = 0;
	if (value[i] == '-')
		i++;
	while (ft_isspace(value[i]))
		i++;
	while (value[i])
	{
		if ((value[i] == '\'' || value[i] == '\"') && tmp == 0)
			tmp = value[i];
		else if (value[i] == tmp && tmp != 0)
			tmp = 0;
		else
		{
			*new_value[j] = value[i];
			j++;
		}
		i++;
	}
}

char	*take_delim(t_redir *rd)
{
	char	*delimiter;	
	char	*new_delim;

	delimiter = rd->file + 2;
	new_delim = malloc(ft_strlen(delimiter));
	if (!new_delim)
		return (NULL);
	format_delimiter(delimiter, &new_delim, 0, 0);
	return (new_delim);
}

char	*hdoc_new_val(t_redir *rd, char *input, t_sh_params *sh_params)
{
	int		i;
	char	*delimiter;
	char	*new_input;

	delimiter = rd->file;
	if (ft_strchr(delimiter, '\"') || ft_strchr(delimiter, '\''))
		return (input);
	new_input = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && !(ft_strchr("\'\"", input[i + 1])))
			i = expand_params(input, &new_input, i, sh_params);
		else
		{
			new_input = join_char(new_input, input[i]);
			i++;
		}
	}
	free(input);
	return (new_input);
}

void	change_heredoc(t_cmd **cmd, char *file, t_sh_params **sh_params)
{
	t_redir	**redir;
	t_list	**tmp_file;

	redir = &((*cmd)->redir);
	free((*redir)->file);
	(*redir)->file = ft_strdup(file);
	(*redir)->type = TK_REDIR_IN;
	tmp_file = &((*sh_params)->tmp_file);
	ft_lstadd_back(tmp_file, ft_lstnew(file));
}
