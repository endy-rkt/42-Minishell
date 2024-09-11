/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:35:02 by trazanad          #+#    #+#             */
/*   Updated: 2024/09/11 15:44:23 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

# include "../header.h"

t_token	*lex(char *input, t_sh_params **sh_params);
void	add_token(t_token **tk, token_type type, char *str, int len);
int		take_word_len(char *str, int i);
int		handle_operator(char *str, t_token **tk);
int		is_redir(t_token *tk);
t_token	*tk_create(char *value, token_type type, t_token *tk_prev);
t_token	*tk_last(t_token *tk);
void	tk_add_back(t_token **tk, t_token *tk_new);
void	tk_clear(t_token **tk);
int		check_tk_error(t_token **tk, t_sh_params **sh_params);
int		redir_error(t_token **tk);
int		my_perror(int status, char *str);
void	expand(t_token **tk, t_sh_params *sh_params);
int		expand_params(char *value, char **new_value, int i, t_sh_params *sh_params);
int		expand_single_quote(char *value, char **new_value, int i);
int		expand_double_quote(char *value, char **new_value, int i, t_sh_params *sh_params);
char	*join_char(char *new_value, char c);

#endif