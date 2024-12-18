/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:09:24 by trazanad          #+#    #+#             */
/*   Updated: 2024/11/03 14:47:39 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_redir(t_token *tk)
{
	int	is_redirin;
	int	is_redirout;

	is_redirin = (tk->type == TK_REDIR_IN || tk->type == TK_REDIR_IN2);
	is_redirout = (tk->type == TK_REDIR_OUT || tk->type == TK_REDIR_APPEND);
	return (is_redirin || is_redirout);
}

int	is_operator(char c)
{
	if (ft_strchr("<>|", c))
		return (1);
	return (0);
}

int	idx_of_first(char *str, char c)
{
	int	i;

	i = 0;
	if (str[0] == 0)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i + 2);
		i++;
	}
	return (1);
}

char	*my_getenv(char *var, t_sh_params *shell_params)
{
	char	*str;

	if (!var)
		return ("");
	str = get_env_value(var, shell_params->my_envp);
	if (!str)
		return ("");
	return (str);
}
