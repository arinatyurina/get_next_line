/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:08:45 by atyurina          #+#    #+#             */
/*   Updated: 2023/11/22 13:12:32 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

ssize_t	index_nl(char *buffer)
{
	ssize_t	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	if (ft_strchr(buffer, '\n') == NULL)
		return (ft_strlen(buffer));
	return (0);
}

ssize_t	index_nl_tr(char *buffer)
{
	ssize_t	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*trim_tail(char *tail)
{
	char	*tr_tail;
	int		nl;

	nl = index_nl_tr(tail);
	if (nl == -1)
	{
		free(tail);
		return (NULL);
	}
	tr_tail = ft_substr(tail, nl + 1, ft_strlen(tail) - nl);
	if (!tr_tail)
	{
		free(tail);
		return (NULL);
	}
	free(tail);
	return (tr_tail);
}

char	*read_fd(int fd, char *tail)
{
	char	*temp_buffer;
	int		bytes_read;

	bytes_read = 1;
	temp_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_buffer)
	{
		free(tail);
		return (NULL);
	}
	while (ft_strchr(tail, '\n') == NULL && bytes_read != 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp_buffer);
			free(tail);
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		tail = dop_func(tail, temp_buffer);
	}
	free(temp_buffer);
	return (tail);
}

char	*get_next_line(int fd)
{
	static char	*tail[4096] = {NULL};
	char		*line;

	if (fd == -1 || fd > SHRT_MAX || read(fd, 0, 0) < 0)
	{
		return (NULL);
	}
	if (!tail[fd])
	{
		tail[fd] = (char *)malloc(sizeof(char) * 1);
		if (!tail[fd])
			return (NULL);
		*tail[fd] = '\0';
	}
	tail[fd] = read_fd(fd, tail[fd]);
	if (!tail[fd] || tail[fd][0] == '\0')
	{
		free(tail[fd]);
		tail[fd] = NULL;
		return (NULL);
	}
	line = ft_substr(tail[fd], 0, index_nl(tail[fd]) + 1);
	tail[fd] = trim_tail(tail[fd]);
	return (line);
}
