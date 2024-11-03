/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 08:53:20 by ferafano          #+#    #+#             */
/*   Updated: 2024/11/03 15:58:51 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H
# define BUILDIN_H
# include "../executor/executor.h"
# include "../header.h"
# include "../libft/libft.h"
# include <ctype.h>

typedef struct s_oldpwd
{
	int		i;
	int		j;
	int		len;
	char	*new_value;
}			t_oldpwd;

typedef struct s_print_exp
{
	int		i;
	int		j;
	int		length;
	int		temp_i;
	char	**temp_env;
}			t_print_exp;

typedef struct s_ext_stat
{
	int		i;
	int		len;
	char	*exist_sign;
	char	*temp;
}			t_ext_stat;

typedef struct s_crt
{
	int		len;
	int		i;
	int		j;
	char	**copy;
	char	*name1;
}			t_crt;

typedef struct s_rem
{
	int		len;
	int		j;
	int		l;
	int		k;
	int		str_len;
	char	**copy;
}			t_rem;

typedef struct s_unset
{
	int		i;
	int		l;
	int		env_name_len;
	char	**temp;
	char	*delimiter;
}			t_unset;

int			ft_check_size(char *s, char c);
int			ft_check_size_array(char *s, char c, int array_indice);
char		**ft_fill_array(char **new_r, char *s, char c);
void		ft_freee(char **new_1, int i);
int			is_null(char **new_1, int i);
void		ft_copy(char *str, char *dest);
char		**ft_copy_env(char **envp);
char		*get_env_value(char *line_read, char **copy_env);
int			ft_cd(char **argv, char ***copy_env);
int			ft_pwd(int fd);
int			ft_env(char **copy_env, char **argv, int fd);
int			ft_export(char **command, char ***env, int fd);
int			print_export(char **copy_env, int fd);
int			validate_name(char *val);
int			ft_unset(char **argv, char ***copy_env);
void		cond_loop(t_print_exp *exp, int *j, int fd);
void		bubble_sort(char **array, int length);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strncpy(char *dest, const char *src, size_t n);
int			buildin(char **argv, t_sh_params **shell_params, int *tab_fd);
int			export_match(char *str_env, char *key);
void		add_new_identifier(char *key, char *value, char ***envp);
int			unset_nb(char **argv, char **env);
char		*export_new_val(char *value, char **key, char *prev_val);
int			ft_exit(char **argv, t_sh_params **shell_params, int *tab_fd);

#endif
