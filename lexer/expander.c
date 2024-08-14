/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:27:04 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/14 16:43:39 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*my_getenv(char *var)
{
	char	*str;

	str = getenv(var);
	if (!str)
		return ("");
	return (str);
}

int	format_params(char *value, char **new_value, int i, int *j)
{
	int		k;
	char	*tmp;
	char	*param_value;

	if (ft_isspace(value[i + 1]) || value[i+1]==0 || value[i+1] == '\'' || value[i+1] == '\"')
	{
		*new_value = ft_strjoin(*new_value, "$");//0
		*j = *j + 1;
	}
	i++;
	if (!(ft_isalpha(value[i]) || value[i] == '_'))
	{
		if (!ft_isspace(value[i]) && value[i] && value[i] != '\'' && value[i] != '\"')
			i++;
		return (i);
	}
	tmp = malloc(ft_strlen(value) + 1);
	k = 0;
	while (ft_isalpha(value[i]) || value[i] == '_')
	{
		tmp[k] = value[i];
		k++;
		i++;
	}
	tmp[k] ='\0';
	param_value = my_getenv(tmp);
	*j = *j + ft_strlen(param_value);
	*new_value = ft_strjoin(*new_value, param_value);//0
	free(tmp);
	return (i);
}

int	format_quoted(char *value, char **new_value, char c, int i)
{
	int		j;
	int		end;

	i++;
	if (c == '\"')
		while (value[i] != c)
		{
			if (value[i] == '$')
				i = format_params(value, new_value, i, &j);
			else
			{
		j = ft_strlen(*new_value);
				*new_value[j] = value[i];
				i++;
			}
		}
	else
	{
		j = ft_strlen(*new_value);
		while (value[i] != c)
		{
			*new_value[j] = value[i];
			i++;
			j++;
		}		
	}	
	if (c == value[i])
		i++;
	return (i);
}

void	expand_word(t_token	**tk)
{
	int		i;
	int		k;
	int		j;
	char 	*tmp;
	char	*value;
	char	*new_value;

	i = 0;
	value = (*tk)->value;
	new_value = malloc(ft_strlen(value) + 1);
	new_value[0] = '\0';
	while (value[i])
	{
		printf("cond=%c\n", value[i]);
		if (value[i] == '\'')
		{
			i++;
			while (value[i] != '\'' && value[i])
			{
			k = 0;
			tmp = malloc(ft_strlen(value) + 1);
			tmp[0] = 0;
			tmp[k] = value[i];
			k++;
			i++;
			tmp[k] = 0;
				j += ft_strlen(tmp);
			new_value = ft_strjoin(new_value, tmp);//0
			free(tmp);
			}
			if (value[i] == '\'')
				i++;
		}
		else if (value[i] == '\"')
			i = format_quoted(value, &new_value, value[i], i);
		else if (value[i] == '$')
			i = format_params(value, &new_value, i, &j);
		else
		{
			k = 0;
			tmp = malloc(ft_strlen(value) + 1);
			tmp[0] = 0;
			tmp[k] = value[i];
			k++;
			i++;
			tmp[k] = 0;
			j += ft_strlen(tmp);
			new_value = ft_strjoin(new_value, tmp);//0
			free(tmp);
		}
		printf("aft=%c\n", value[i]);
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
