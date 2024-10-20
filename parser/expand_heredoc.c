/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:35:14 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/20 09:45:45 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


void	manage_heredoc(t_list	*lst_redir, t_cmd **cmd, char *file, t_sh_params **shell_params)
{
	if (last_redir_in(lst_redir))
		stored_heredoc(cmd, lst_redir, file, shell_params);
	else
		tmp_heredoc(lst_redir, *shell_params);
}

static int	dollared_delim(char *value, char **new_value, int *j, char tmp)
{
	int	i;
	int	dollar_nb;

	dollar_nb = 0;
	i = 0;
	while (value[i] == '$' && tmp == 0)
	{
		if ((value[i + 1] == '\'' || value[i + 1] == '\"'))
		{
			if (dollar_nb % 2 == 1)
			{
				(*new_value)[*j] = value[i];
				*j = *j + 1;
				i++;
			}
			return (i);
		}
		(*new_value)[*j] = value[i];
		*j = *j + 1;
		i++;
		dollar_nb++;
	}
	(*new_value)[*j] = value[i];
	*j = *j + 1;
	return (i);
}

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
			i += dollared_delim(value + i, new_value, &j, tmp);
		i++;
	}
	(*new_value)[j] = '\0';
	*new_value = ft_strjoin(*new_value, "\n");
}

char	*take_delim(t_redir *rd)
{
	char	*delimiter;	
	char	*new_delim;

	delimiter = rd->file;
	new_delim = malloc(ft_strlen(delimiter) + 1);
	if (!new_delim)
		return (NULL);
	format_delimiter(delimiter, &new_delim, 0, 0);
	return (new_delim);
}

char	*hdoc_new_val(t_redir *rd, char *input, t_sh_params *shell_params)
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
			i = expand_params(input, &new_input, i, shell_params);
		else
		{
			new_input = join_char(new_input, input[i]);
			i++;
		}
	}
	free(input);
	return (new_input);
}

