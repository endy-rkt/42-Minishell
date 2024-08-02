/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 08:54:53 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/02 10:17:26 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*create_token(char *value, token_type type, t_token *tk_prev)
{
	t_token	*tk;

	tk = malloc(sizeof(t_token));
	if (!tk)
		return (NULL);
	tk->value = strdup(value); //0
	tk->type = type;
	tk->prev = tk_prev;
	tk->next = NULL;
	return (tk);
}

t_token	*tk_last(t_token *tk)
{
	if (tk)
	{
		if (tk->next)
			return (tk_last(tk->next));
		else
			return (tk);
	}
	return (NULL);
}

void	tk_add_back(t_token **tk, t_token *tk_new)
{
	if (tk)
	{
		if (*tk)
			tk_last(*tk)->next = tk_new;
		else
			*tk = tk_new;
	}	
}

void	tk_clear(t_token **tk)
{
	t_token	*tmp;
	t_token	*tk_next;

	if (tk)
	{
		tmp = *tk;
		while (tmp)
		{
			tk_next = tmp->next;
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			tmp = tk_next;
		}
	}
}

void	tk_print(t_token *tk) //0
{
	t_token	*tmp;

	if (tk)
		printf("value:{%s} type:{%d}\n", tk->value, tk->type);
	else
		return ;
	tmp = tk->next;
	while (tmp)
	{
		printf("value:{%s} type:{%d}\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
}
