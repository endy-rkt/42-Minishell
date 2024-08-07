/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:52:23 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/07 13:44:17 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_type()
{
	token_type type []={
	TK_WORD,//0
    TK_PIPE,//1
	TK_REDIR,//2
    TK_REDIR_IN,//3
    TK_REDIR_OUT,//4
    TK_REDIR_OUT2,//5
    TK_HEREDOC,//6
	TK_OR,//7
	TK_AND,//8
	TK_WILDCARD,//9
	TK_L_PAREN,//10
	TK_R_PAREN};//11
	for (int i = 0; i < 12; i++)
	{
		printf("%d\t--",type[i]);
	}
		printf("\n");

}
int	main(int argc, char *argv[]/*, char *envp[]void*/)
{
	t_token	*tk;
	char	*str;

	printf("%s\n",argv[1]);
	if (argc < 1)
		return (0);
	//str = ft_strdup(argv[1]);
	//print_type();
	tk = lex(argv[1]);
	tk_print(tk);
	tk_clear(&tk);
	return (0);
}
