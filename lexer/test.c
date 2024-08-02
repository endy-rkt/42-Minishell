/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:03:01 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/02 10:12:51 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	main(void)
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
}
