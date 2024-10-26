/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:31:32 by trazanad          #+#    #+#             */
/*   Updated: 2024/10/25 12:11:46 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char    *get_env_value(char *key, char **envp)
{
    int     i;
    int     len;
    char    *tmp_key;

    if (envp == NULL)
        return (NULL);
    i = 0;
    tmp_key = ft_strdup(key);
    tmp_key = ft_strjoin(tmp_key, "=");
    len = ft_strlen(tmp_key);
    while (envp[i])
    {
        if (ft_strncmp(tmp_key, envp[i], len) == 0)
        {
            free(tmp_key);
            return (envp[i] + len);
        }
        i++;
    }
    free(tmp_key);
    return (NULL);
}

void    update_envp(char *key, char *value, char ***envp)
{
        
}

int change_to_path(char *path, char ***envp)
{
    int     status;
    char    *old_path;
    char    current_path[4096];

    status = 0;
    getcwd(current_path, sizeof(current_path));
    if (ft_strcmp(path, "-") == 0)
    {
        old_path = get_env_value("OLDPWD", *envp);
        if (old_path == NULL)
        {
            ft_putchar_fd("minishell: cd: OLDPWD not set\n", 2);
            return (1);
        }
        if (!chdir(old_path))
        {
            perror("cd");
            return (1);
        }
        update_envp("OLDPWD", current_path, envp);
        getcwd(current_path, sizeof(current_path));
        update_envp("PWD", current_path, envp);
    }
    else
    {
        if (chdir(path))
        {
            perror("cd");
            return (1);
        }
        update_envp("OLDPWD", current_path, envp);
        getcwd(current_path, sizeof(current_path));
        update_envp("PWD", current_path, envp);
    }
    return (status);
}

int navigate_to_home(char **argv, char ***envp)
{
    char    *home_path;

    home_path = get_env_value("HOME", *envp);
    if (home_path == NULL)
    {
        ft_putchar_fd("minishell: cd: HOME not set\n", 2);
        return (1);
    }
}

int ft_cd(char **argv, char ***envp)
{
    int status;

    status = 0;
    if (argv[1] == NULL)
        status = navigate_to_home(argv, envp);
    else if (argv[2] != NULL)
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        return (1);
    }
    else
        status = change_to_path(argv, envp);
    return (status);
}
