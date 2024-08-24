/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:52:23 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/24 09:31:56 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_type()
{
	token_type type []={
	TK_WORD,//0
    TK_PIPE,//1
    TK_REDIR_IN,//3
    TK_REDIR_OUT,//4
    TK_REDIR_APPEND,//5
    TK_HEREDOC//6
	};//11
	for (int i = 0; i < 12; i++)
	{
		printf("%d\t--",type[i]);
	}
		printf("\n");

}


void	lex_test(char *input)
{
	int		input_error;
	t_token	*tk;
	t_cmd	*cmd;

	tk = lex(input);
	input_error = expand(&tk);
	tk_print(tk);
	cmd = parser_test(tk);
	print_single_cmd(cmd);
	tk_clear(&tk);
}

int	main(void/*, char *envp[]void*/)
{
	handle_input0(lex_test);
	return (0);
}
