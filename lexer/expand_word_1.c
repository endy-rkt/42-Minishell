/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:31:59 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/19 15:31:13 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	add_tk(t_token **tk, t_token **tk_new, t_token *tk_next, t_list *tmp)
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

static void	add_value(t_token **tk, char **new_value, t_list **lst_word)
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

void	apply_expansion(t_token **tk, t_list **lst_word, char **new_val, char **value)
{
	int	empty_val;
	int	quoted_value;

	if ( *new_val == NULL || (*new_val && *lst_word == NULL))
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
