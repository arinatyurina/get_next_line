/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:19:20 by atyurina          #+#    #+#             */
/*   Updated: 2023/11/21 20:35:23 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE (5)
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	*read_fd(int fd, char *tail);
ssize_t	index_nl(char *buffer);
ssize_t	index_nl_tr(char *buffer);
char	*trim_tail(char *tail);
char	*dop_func(char *tail, char *temp_buffer);

#endif
