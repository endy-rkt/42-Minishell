/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:50:40 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/03 15:00:40 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_void_redir(t_token *tk)
{
	char	msg[100];

	ft_strcpy(msg, "minishell: syntax error near unexpected token `newline'\n");
	while (tk)
	{
		if (is_redir(tk))
		{
			if (tk->next == NULL)
				return (my_perror(2, msg));
			if (tk->next->value == NULL)
				return (my_perror(1, "minishell: ambiguous redirect\n"));
		}
		tk = tk->next;
	}
	return (0);
}

int	is_directory(char *args)
{
	struct stat	sb;

	if (args == NULL)
		return (0);
	if (lstat(args, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
		{
			print_exec_error(args, "Is a directory\n");
			return (1);
		}
	}
	return (0);
}
