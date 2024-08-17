/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:27:04 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/17 09:31:17 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*my_getenv(char *var)
{
	char	*str;

	if (!var)
		return ("");
	str = getenv(var);
	if (!str)
		return ("");
	return (str);
}

char	*join_char(char *new_value, char c)
{
	char	*tmp;
	char	*str;

	tmp = malloc(2);
	if (!tmp)
		return (NULL);
	tmp[0] = c;
	tmp[1] = '\0';
	str = ft_strjoin(new_value, tmp);
	free(tmp);
	return (str);
}

int	expand_single_quote(char *value, char **new_value, int i)
{
	i++;
	while (value[i] && value[i] != '\'')
	{
		*new_value = join_char(*new_value, value[i]);
		i++;
	}
	if (value[i] == '\'')
		i++;
	return (i);
}

int	expand_params(char *value, char **new_value, int i)
{
	int		j;
	char	*tmp;

	i++;
	tmp = ft_strdup("");
	if (value[i] == '\'' || value[i] == '\"')
		return (i);
	else if (value[i] == '\0' || ft_isspace(value[i]))
	{
		*new_value = ft_strjoin(*new_value, "$");
		return (i);
	}
	else if (value[i] == '?')//to handle dude //0
	{
		tmp = join_char(tmp, value[i]);
		*new_value = ft_strjoin(*new_value, tmp);//0
		free(tmp);
		return (i + 1);
	}
	else if (ft_strchr("$!#*@-", value[i]) || ft_isdigit(value[i]))
	{
		tmp = join_char(tmp, value[i]);
		*new_value = ft_strjoin(*new_value, my_getenv(tmp));
		free(tmp);
		return (i + 1);
	}
	else if (!(ft_isalpha(value[i]) || value[i] == '_'))
	{
		tmp = join_char(tmp, '$');
		tmp = join_char(tmp, value[i]);
		*new_value = ft_strjoin(*new_value, tmp);
		free(tmp);
		return (i + 1);
	}
	else
	{
		while (ft_isalpha(value[i]) || value[i] == '_' || ft_isdigit(value[i]))
		{
			tmp = join_char(tmp, value[i]);
			i++;
		}
		*new_value = ft_strjoin(*new_value, my_getenv(tmp));
		free(tmp);
		return (i);
	}
}

int		expand_double_quote(char *value, char **new_value, int i)
{
	i++;
	while (value[i] && value[i] != '\"')
	{
		if (value[i] == '$')
		{
			if (value[i + 1] == '\'')
				*new_value = ft_strjoin(*new_value, "$");
			i = expand_params(value, new_value, i);
		}
		else
		{
			*new_value = join_char(*new_value, value[i]);
			i++;
		}
	}
	if (value[i] == '\"')
		i++;
	return (i);
}

void	expand_word(t_token	**tk)
{
	int		i;
	char	*value;
	char	*new_value;

	i = 0;
	value = (*tk)->value;
	new_value = ft_strdup("");
	while (value[i])
	{
		if (value[i] == '\'')
			i = expand_single_quote(value, &new_value, i);
		else if (value[i] == '\"')
			i = expand_double_quote(value, &new_value, i);
		else if (value[i] == '$')
			i = expand_params(value, &new_value, i);
		else
		{
			new_value = join_char(new_value, value[i]);
			i++;
		}
	}
	free(value);
	(*tk)->value = new_value;
}

int	format_delimiter(char *value, char *new_value, int i, int j)
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
			new_value[j] = value[i];
			j++;
		}
		i++;
	}
	return (j);
}

void	expand_redir(t_token **tk)
{
	int		i;
	int		j;
	char	*value;
	char	*new_value;

	i = 0;
	j = 0;
	value = (*tk)->value;
	while (value[i] == '0')
		i++;
	new_value = malloc(ft_strlen(value) + 1);
	while ((ft_isdigit(value[i]) || ft_strchr("<>", value[i])) && value[i])
	{
		new_value[j] = value[i];
		i++;
		j++;
	}
	if ((*tk)->type == TK_HEREDOC)
		j = format_delimiter(value, new_value, i, j);
	new_value[j] = '\0';
	free(value);
	(*tk)->value = new_value;
}

void	expand_token(t_token **tk)
{
	if (*tk)
	{
		if ((*tk)->type == TK_WORD)
			expand_word(tk);
		if ((*tk)->type == TK_REDIR_IN || (*tk)->type == TK_REDIR_OUT 
			|| (*tk)->type == TK_REDIR_OUT2  || (*tk)->type == TK_HEREDOC)
			expand_redir(tk);
		// if ((*tk)->type == TK_L_PAREN);
		// if ((*tk)->type == TK_R_PAREN);
		if ((*tk)->next)
			expand_token(&((*tk)->next));
	}
}

void	expand(t_token  **tk)
{
	if (!*tk)
		return ;
	expand_token(tk);
	// if(input_error(*tk))
	// 	tk_clear(tk);
}
