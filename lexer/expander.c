/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:21:48 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/18 09:17:54 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	verify_assign(t_token **tk)
{
	int		i;
	char	*value;

	value = (*tk)->value;
	if (!ft_strchr(value, '='))
		return ;
	i = 0;
	if (ft_isdigit(value[i]) || value[0] == '=')
		return ;
	while (value[i] && value[i] != '=')
	{
		if (!(ft_isalnum(value[i]) || value[i] == '_'))
			return ;
		i++;
	}
	(*tk)->type = TK_ASSIGN;
}

int	join_token(char **splitted_word, int count, t_list **lst_word)
{
	t_list	*new;
	char	*init_content;

	while (splitted_word[count])
	{
		if (count == 0 && *lst_word)
		{
			init_content = ft_strjoin((*lst_word)->content, splitted_word[count]);
			(*lst_word)->content = init_content;
		}
		else
		{
			new = ft_lstnew(ft_strdup(splitted_word[count]));
			ft_lstadd_back(lst_word, new);
		}
		count++;
	}
	free_args(splitted_word);
	return (count);
}

int	void_params(char **new_value, char *value)
{
	int	quoted_params;

	quoted_params = ft_strcmp(value, "$\"\"") && ft_strcmp(value, "$\'\'");
	if ((*new_value)[0] == '\0' && quoted_params)
	{
		free(*new_value);
		*new_value = NULL;
		return (1);
	}
	return (0);
}

int	handle_params(t_list **lst_word, char *value, char **new_value, t_sh_params *shell_params)
{
	int		i;
	int		len;
	int		count;
	char	**splitted_word;

	i = 0;
	count = ft_strlen(*new_value);
	i = expand_params(value, new_value, i, shell_params);
	if (void_params(new_value, value))
		return (i);
	len = ft_strlen(*new_value);
	if (len == count)
		return (i);
	splitted_word = ft_split(*new_value, ' ');
	if ((*new_value)[len - 1] == ' ' && !splitted_word && value[i])
		ft_lstadd_back(lst_word, ft_lstnew(ft_strdup("")));
	if (!splitted_word)
		return (i);
	count = join_token(splitted_word, 0, lst_word);
	if ((*new_value)[len - 1] == ' ' && value[i])
		ft_lstadd_back(lst_word, ft_lstnew(ft_strdup("")));
	(*new_value)[0] = '\0';
	return (i);
}

void	add_tk(t_token **tk, t_token **tk_new, t_token *tk_next, t_list *tmp)
{
	t_token	*new;

	while (tmp)
	{
		tmp = tmp->next;
		if (tmp)
		{
			new = tk_create(tmp->content, TK_WORD, (*tk_new)->prev);
			tk_add_back(tk_new, new);
		}
	}
	if (tk_new)
	{
		tk_add_back(tk_new, tk_next);
		(*tk)->next = *tk_new;
	}
}

void	add_value(t_token **tk, char **new_value, t_list **lst_word)
{
	t_list	*tmp;
	t_list	*last_lst;
	t_token	*tk_new;
	t_token	*tk_next;

	if (*lst_word == NULL)
		*lst_word = ft_lstnew(ft_strdup(""));
	last_lst = ft_lstlast(*lst_word);
	last_lst->content = ft_strjoin(last_lst->content, *new_value);
	tk_next = (*tk)->next;
	(*tk)->value = ft_strdup((*lst_word)->content);
	tmp = (*lst_word)->next;
	tk_new =NULL;
	if (tmp)
		tk_new = tk_create(tmp->content, TK_WORD, *tk);
	add_tk(tk, &tk_new, tk_next, tmp);
}

static void	apply_expansion(t_token **tk, t_list **lst_word, char **new_val, char **value)
{
	int	empty_val;
	int	quoted_value;

	if ((*new_val && *lst_word == NULL) || *new_val == NULL)
	{
		free(*value);
		(*tk)->value = *new_val;
		return ;
	}
	quoted_value = (ft_strchr(*value, '\'') || ft_strchr(*value, '\"'));
	empty_val = ((*new_val)[0] != 0 && !quoted_value);
	if (*lst_word != NULL || empty_val)
	{
		add_value(tk, new_val, lst_word);
		free(*value);
		*value = NULL;
	}
	else
	{
		free(*value);
		(*tk)->value = NULL;
	}
	if (*lst_word)
		ft_lstclear(lst_word, free_assign);
}

static void	expand_word(t_token	**tk, t_sh_params *shell_params)
{
	int		i;
	char	*value;
	char	*new_value;
	t_list	*lst_word;

	i = 0;
	value = (*tk)->value;
	new_value = ft_strdup("");
	lst_word = NULL;
	while (value[i])
	{
		if (value[i] == '\'')
			i = expand_single_quote(value, &new_value, i);
		else if (value[i] == '\"')
			i = expand_double_quote(value, &new_value, i, shell_params);
		else if (value[i] == '$')
			i += handle_params(&lst_word, value + i, &new_value, shell_params);	
		else
		{
			new_value = join_char(new_value, value[i]);
			i++;
		}
	}
	apply_expansion(tk, &lst_word, &new_value, &value);
}

static void	expand_redir(t_token **tk)
{
	int		i;
	int		j;
	char	*value;
	char	*new_value;

	i = 0;
	j = 0;
	value = (*tk)->value;
	new_value = malloc(ft_strlen(value) + 1);
	if (!new_value)
		return ;
	while (ft_strchr("<>", value[i]) && value[i])
	{
		new_value[j] = value[i];
		i++;
		j++;
	}
	new_value[j] = '\0';
	free(value);
	(*tk)->value = new_value;
}

static void	recursive_expansion(t_token **tk, t_sh_params *shell_params)
{
	if (*tk)
	{
		if ((*tk)->type == TK_WORD || (*tk)->type == TK_ASSIGN)
		{
			verify_assign(tk);
			expand_word(tk, shell_params);
		}
		if (is_redir(*tk))
			expand_redir(tk);
		if ((*tk)->next)
			recursive_expansion(&((*tk)->next), shell_params);
	}
}

void	expand(t_token **tk, t_sh_params *shell_params)
{
	if (!tk || (*tk) == NULL)
		return ;
	recursive_expansion(tk, shell_params);
}
