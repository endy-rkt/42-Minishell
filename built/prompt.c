/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:13:08 by ferafano          #+#    #+#             */
/*   Updated: 2024/09/09 09:13:22 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

void pwd_prompt(char *path)
{
	const char *blue = "\033[0;33m";
    const char *reset = "\033[0m";
	char	cwd[4096];
	int		i;
	int		count;

	if (chdir(path) != 0)
	{
 		i = 0;
		count = 0;
        getcwd(cwd, sizeof(cwd)); 
		while (count < 3)
		{
			if (cwd[i] == '/')
				count++;
			i++;
		}
		write(1, blue, strlen(blue));
		write(1, "~/", 2);
		while (cwd[i])
		{	
			write(1, &cwd[i], 1);
			i++;
		}
		write(1, reset, strlen(reset));
    }
	else
        perror("cd");
}

void ft_pwd(char *path)
{
	char	pwd[1024];
	int		i;

	if (chdir(path) != 0)
	{
 		i = 0;
        getcwd(pwd, sizeof(pwd)); 
		while (pwd[i])
		{	
			write(1, &pwd[i], 1);
			i++;
		}
    }
	else
        perror("cd");
	write (1, "\n", 1);
}
