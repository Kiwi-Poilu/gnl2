/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sobouatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:28:08 by sobouatt          #+#    #+#             */
/*   Updated: 2021/02/08 23:52:55 by sobouatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <libc.h>

int		check_end(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		where(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

void	save_space(char **save, char **line)
{
	if (check_end(*save) == 1)
	{
		*line = ft_substr(*save, 0, where(*save), 0);
		*save = ft_substr(*save, where(*save) + 1, ft_strlen(*save), 1);
	}
	else
	{
		*line = ft_substr((*save), 0, ft_strlen(*save), 1);
		*save = NULL;
	}
}

int		get_next_line(int fd, char **line)
{
	static char	*save[65535];
	char		*buffer;
	int			read_rt;

	read_rt = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (check_end(save[fd]) != 1 && read_rt != 0)
	{
		read_rt = read(fd, buffer, BUFFER_SIZE);
		if (read_rt == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[read_rt] = '\0';
		save[fd] = ft_strjoin(save[fd], buffer);
	}
	save_space(&save[fd], line);
	free(buffer);
	return (read_rt == 0 && save[fd] == NULL ? 0 : 1);
}

int		main(void)
{
	int fd;
	int fd2;
	char *line;
	
	fd = open("text", O_RDONLY);
	fd2 = open("text", O_RDONLY);

	get_next_line(fd, &line);
		printf("%s\n", line);
	get_next_line(fd2, &line);
		printf("%s\n", line);
	get_next_line(fd, &line);
		printf("%s\n", line);
	get_next_line(fd2, &line);
		printf("%s\n", line);
	get_next_line(fd2static, &line);
		printf("%s\n", line);
}
