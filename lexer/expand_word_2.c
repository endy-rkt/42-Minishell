/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:39:17 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/19 15:12:19 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	join_token(char **splitted_word, int count, t_list **lst_word)
{
	t_list	*new;
	char	*init_content;

	while (splitted_word[count])
	{
		if (count == 0 && *lst_word)
		{
			init_content = ft_strjoin((*lst_word)->content, splitted_word[count]);
			(*lst_word)->content = init_content;
		}
		else
		{
			new = ft_lstnew(ft_strdup(splitted_word[count]));
			ft_lstadd_back(lst_word, new);
		}
		count++;
	}
	free_args(splitted_word);
	return (count);
}

static int	void_params(char **new_value, char *value)
{
	int	quoted_params;

	quoted_params = ft_strcmp(value, "$\"\"") && ft_strcmp(value, "$\'\'");
	if ((*new_value)[0] == '\0' && quoted_params)
	{
		free(*new_value);
		*new_value = NULL;
		return (1);
	}
	return (0);
}

int	handle_params(t_list **lst_word, char *value, char **new_value, t_sh_params *shell_params)
{
	int		i;
	int		len;
	int		count;
	char	**splitted_word;

	i = 0;
	count = ft_strlen(*new_value);
	i = expand_params(value, new_value, i, shell_params);
	if (void_params(new_value, value))
		return (i);
	len = ft_strlen(*new_value);
	if (len == count)
		return (i);
	splitted_word = ft_split(*new_value, ' ');
	if (!splitted_word && (*new_value)[len - 1] == ' ' && value[i])
		ft_lstadd_back(lst_word, ft_lstnew(ft_strdup("")));
	if (!splitted_word)
		return (i);
	count = join_token(splitted_word, 0, lst_word);
	if ((*new_value)[len - 1] == ' ' && value[i])
		ft_lstadd_back(lst_word, ft_lstnew(ft_strdup("")));
	(*new_value)[0] = '\0';
	return (i);
}
