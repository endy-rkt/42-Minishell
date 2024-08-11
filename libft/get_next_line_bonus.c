/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 08:31:15 by trazanad          #+#    #+#             */
/*   Updated: 2024/08/11 14:08:50 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

char	*ft_get_one_line(char	*remining_str)
{
	int		i;
	char	*str;

	i = 0;
	if (!remining_str[i])
		return (0);
	while (remining_str[i] && remining_str[i] != '\n')
		i++;
	str = (char *)malloc(i + 2);
	i = 0;
	while (remining_str[i] && remining_str[i] != '\n')
	{
		str[i] = remining_str[i];
		i++;
	}
	if (remining_str[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_read_buf(int fd, char *remining_str)
{
	char	*buf;
	int		read_res;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	read_res = 1;
	buf[0] = '\0';
	while (!ft_strchr(buf, '\n') && read_res != 0)
	{
		read_res = read(fd, buf, BUFFER_SIZE);
		if (read_res == -1)
		{
			free(buf);
			return (0);
		}
		buf[read_res] = '\0';
		remining_str = ft_strjoin(remining_str, buf);
	}
	free(buf);
	return (remining_str);
}

char	*ft_renew_remining_str(char *remining_str)
{
	char	*str;
	int		len_line;
	int		i;

	len_line = 0;
	while (remining_str[len_line] && remining_str[len_line] != '\n')
		len_line++;
	if (!remining_str[len_line])
	{
		free(remining_str);
		return (0);
	}
	str = (char *)malloc(ft_strlen(remining_str) - len_line + 1);
	if (!str)
		return (0);
	i = 0;
	len_line++;
	while (remining_str[len_line])
		str[i++] = remining_str[len_line++];
	str[i] = '\0';
	free(remining_str);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*remining_str[1024];
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
	{
		free(remining_str[fd]);
		return (0);
	}
	if (fd == 0)
		ft_printf(">> ");
	remining_str[fd] = ft_read_buf(fd, remining_str[fd]);
	if (!remining_str[fd])
		return (0);
	line = ft_get_one_line(remining_str[fd]);
	remining_str[fd] = ft_renew_remining_str(remining_str[fd]);
	if (strcmp(line, "exit\n") == 0)
	{
		free(line);
		return (0);
	}
	return (line);
}
