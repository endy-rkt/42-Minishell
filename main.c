/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:52:23 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/02 11:34:34 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(/*int argc, char *argv[], char *envp[]*/void)
{
	t_token	*tk;
	t_token *tmp;

	tk = NULL;
	if (!tk)
		tk = create_token("abc", TK_WORD, tk_last(tk));
	tmp = create_token("tmp", TK_WORD, tk_last(tk));
	tk->next = tmp;
	tk_print(tk);
	tk_clear(&tk);
	return (0);
	return (0);
}
