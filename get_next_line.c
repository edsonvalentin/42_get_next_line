/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:35:57 by evalenti          #+#    #+#             */
/*   Updated: 2023/07/08 15:52:34 by evalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_buffer(int fd, char *buffer)
{
	char	*tmp_buffer;
	int		chars_read;

	tmp_buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp_buffer)
		return (NULL);
	chars_read = 1;
	while (!(ft_strchr(buffer, '\n')) && chars_read != 0)
	{
		chars_read = read(fd, tmp_buffer, BUFFER_SIZE);
		if (chars_read == -1)
		{
			free(tmp_buffer);
			free(buffer);
			return (NULL);
		}
		tmp_buffer[chars_read] = '\0';
		buffer = ft_strjoin(buffer, tmp_buffer);
	}
	free(tmp_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_get_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	new_line = ft_get_line(buffer);
	buffer = ft_clean_buffer(buffer);
	return (new_line);
}
