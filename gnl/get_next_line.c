/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delrio <delrio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 03:00:41 by delrio            #+#    #+#             */
/*   Updated: 2025/03/31 20:27:42 by delrio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*readfd(int fd, char *buffer)
{
	char	*buffertemp;
	ssize_t	bytesreaded;

	buffertemp = malloc(BUFFER_SIZE + 1);
	if (!buffertemp)
		return (free(buffer), NULL);
	bytesreaded = 1;
	while (bytesreaded > 0 && !ft_strchr(buffer, '\n'))
	{
		bytesreaded = read(fd, buffertemp, BUFFER_SIZE);
		if (bytesreaded < 0)
			return (free(buffertemp), free(buffer), NULL);
		buffertemp[bytesreaded] = '\0';
		buffer = ft_strjoin(buffer, buffertemp);
		if (!buffer)
			return (free(buffertemp), NULL);
	}
	free(buffertemp);
	return (buffer);
}

static char	*process_line(char **buffer)
{
	char	*line;
	char	*temp;
	size_t	i;

	if (!*buffer)
		return (NULL);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	line = ft_substr(*buffer, 0, i + ((*buffer)[i] == '\n'));
	temp = ft_strdup(*buffer + i + ((*buffer)[i] == '\n'));
	free(*buffer);
	*buffer = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = readfd(fd, buffer);
	if (!buffer)
		return (NULL);
	line = process_line(&buffer);
	if (!line || (line[0] == '\0'))
	{
		free(line);
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (line);
}

// int main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	if (argc < 2)
// 		return (write(2, "Usage: ./a.out <filename>\n", 26), 1);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (write(2, "Error opening file\n", 20), 1);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
