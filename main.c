/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:52:23 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 13:03:28 by trazanad         ###   ########.fr       */
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

t_sh_params	*init_sh_params(t_ast *ast, t_list *tmp_file, char **my_envp, char **my_export)
{
	t_sh_params	*init_params;

	init_params = malloc(sizeof(t_sh_params));
	if (!init_params)
		return (NULL);
	init_params->ast = ast;
	init_params->exit_status = 0;
	init_params->tmp_file = tmp_file;
	init_params->my_envp = my_envp;
	init_params->my_export = my_export;
	return (init_params);
}

void	lex_test(char *input)
{
	int		input_error;
	t_token	*tk;
	t_sh_params	*sh_params;
	t_ast	*ast;

	tk = lex(input);
	input_error = expand(&tk);
	tk_print(tk);
	ast = create_ast(tk);
	sh_params = init_sh_params(ast, NULL, NULL, NULL);
	// print_ast(ast);
	// printf("------------cmd---------------------\n");
	execute_ast(ast);
	tk_clear(&tk);
}

void handle_sigint(int sig)
{
    (void)sig;
    // Print a new prompt after catching Ctrl+C
    write(STDOUT_FILENO, "\n>>", 3);
}

int	main(void/*, char *envp[]void*/)
{
	signal(SIGINT, handle_sigint);
	handle_input0(lex_test);
	return (0);
}
