/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:48:16 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 15:10:44 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*tk_create(char *value, token_type type, t_token *tk_prev)
{
	t_token	*tk;

	tk = malloc(sizeof(t_token));
	if (!tk)
		return (NULL);
	tk->value = value;
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
		if (*tk)
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
}

void	tk_print(t_token *tk) //to remove
{
	t_token	*tmp;

	if (tk)
	{
		if (!tk->next)
			printf("value:{%s} type:{%d}\n", tk->value, tk->type);
		else
		printf("value:{%s} type:{%d} next:{%s}\n", tk->value, tk->type, tk->next->value);
	}
	else
		return ;
	tmp = tk->next;
	while (tmp)
	{
		if (!tmp->next)
			printf("value:{%s} type:{%d} prev:{%s}\n", tmp->value, tmp->type, tmp->prev->value);
		else
			printf("value:{%s} type:{%d} next:{%s} prev:{%s}\n", tmp->value, tmp->type, tmp->next->value, tmp->prev->value);
		tmp = tmp->next;
	}
}
