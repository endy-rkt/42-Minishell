/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:21:48 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/10 12:58:57 by trazanad         ###   ########.fr       */
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
//
static void	expand_word0(t_token	**tk, t_sh_params *shell_params)
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
			i = expand_double_quote(value, &new_value, i, shell_params);
		else if (value[i] == '$')
			i = expand_params(value, &new_value, i, shell_params);
		else
		{
			new_value = join_char(new_value, value[i]);
			i++;
		}
	}
	free(value);
	(*tk)->value = new_value;
}


// void	print_list(t_list *lst)
// {
// 	if (lst)
// 	{
// 		if (lst->content)
// 		printf("val:{%s}\n", (char*)lst->content);
// 		if (lst -> next)
// 			print_list(lst -> next);
// 	}
// }

int	handle_params(t_list **lst_word, char *value, char **new_value, t_sh_params *shell_params)
{
	int		i;
	int		count;
	char	**splitted_word;

	i = 0;
	count = ft_strlen(*new_value);
	i = expand_params(value, new_value, i, shell_params);
	if (ft_strlen(*new_value) == count)
		return (i);
	splitted_word = ft_split(*new_value, ' ');
	if ((*new_value)[ft_strlen(*new_value) - 1] == ' ' && !splitted_word && value[i])
		ft_lstadd_back(lst_word, ft_lstnew(ft_strdup("")));
	if (!splitted_word)
		return (i);
	count = 0;
	while (splitted_word[count])
	{
		if (count == 0 && *lst_word)
			(*lst_word)->content = ft_strjoin((*lst_word)->content, splitted_word[count]);
		else
			ft_lstadd_back(lst_word, ft_lstnew(ft_strdup(splitted_word[count])));
		count++;
	}
	if ((*new_value)[ft_strlen(*new_value) - 1] == ' ' && value[i])
		ft_lstadd_back(lst_word, ft_lstnew(ft_strdup("")));
	(*new_value)[0] = '\0';
	return(i);
}

void	add_expansion(t_token **tk, char **new_value, t_list **lst_word)
{
	t_list	*tmp;
	t_token	*tk_next;
	t_token	*tk_new;
	t_list	*last_lst;
	char	*content;

	if (*lst_word == NULL)
		*lst_word = ft_lstnew(ft_strdup(""));
	last_lst = ft_lstlast(*lst_word);
	if (last_lst == NULL)
	{
		return ;
	}
	last_lst->content = ft_strjoin(last_lst->content, *new_value);
	tk_next = (*tk)->next;
	(*tk)->value = ft_strdup((*lst_word)->content);
	tmp = (*lst_word)->next;
	tk_new =NULL;
	if (tmp)
		tk_new = tk_create(tmp->content, TK_WORD, *tk);
	while (tmp)
	{
		tmp = tmp->next;
		if (tmp)
			tk_add_back(&tk_new, tk_create(tmp->content, TK_WORD, tk_new->prev));
	}
	//free list
	if (tk_new)
	{
		tk_add_back(&tk_new, tk_next);
		(*tk)->next = tk_new;
	}
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
	if (!(new_value[0] == 0 && !(ft_strchr(value, '\'') || ft_strchr(value, '\"')) && lst_word == NULL))
		add_expansion(tk, &new_value, &lst_word);
	else
		(*tk)->value = NULL;
	free(value);
	value = NULL;
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

static void	expand_token(t_token **tk, t_sh_params *shell_params)
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
			expand_token(&((*tk)->next), shell_params);
	}
}

void	expand(t_token **tk, t_sh_params *shell_params)
{
	if (!tk || (*tk) == NULL)
		return ;
	expand_token(tk, shell_params);
}
