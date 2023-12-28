/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:08:45 by atyurina          #+#    #+#             */
/*   Updated: 2023/11/22 14:48:56 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		return (ft_strlen(buffer)); //if there is line without new line we need to return this line
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
	if (nl == -1) //this means there is no nl
	{
		free(tail);
		return (NULL);
	}
	tr_tail = ft_substr(tail, nl + 1, ft_strlen(tail) - nl);
	if (!tr_tail) //if not worked need to free
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

	bytes_read = 1; //for while to work for the first time 
	temp_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char)); // malloc temp)buff for reading
	if (!temp_buffer)
	{
		free(tail);
		return (NULL);
	}
// strchr returns NULL is no new line, else pointer to new line
	while (ft_strchr(tail, '\n') == NULL && bytes_read != 0) 
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1) //if error
		{
			free(temp_buffer);
			free(tail);
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		tail = dop_func(tail, temp_buffer); //strjoin (tail, temp_buf)
	}
	free(temp_buffer); //freeing temp_buffer cause its no longer needed
	return (tail);
}

char	*get_next_line(int fd)
{
	static char	*tail = NULL;
	char		*line;

// checking if 1)fd is opened 2)max amoumt of fd
	if (fd == -1 || fd > 4095 || BUFFER_SIZE < 1)
		return (NULL);
// mallocing tail in case its empty so that it is identidied and it exists
	if (!tail)
	{
		tail = (char *)malloc(sizeof(char) * 1);
		if (!tail)
			return (NULL);
		*tail = '\0';
	}
	tail = read_fd(fd, tail);
// if there is nothing in tail we need to free memory 
// and tail = null to get rid of garbage
	if (!tail || tail[0] == '\0')
	{
		free(tail);
		tail = NULL;
		return (NULL);
	}
// get line from tail
	line = ft_substr(tail, 0, index_nl(tail) + 1);
//	trim tail after new line
	tail = trim_tail(tail);
	return (line);
}
