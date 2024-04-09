/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtcza <mwojtcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:13:44 by mwojtcza          #+#    #+#             */
/*   Updated: 2024/04/09 16:14:22 by mwojtcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*linex(char *left)
{
	int		i;
	char	*str;

	i = 0;
	if (!left[i])
		return (NULL);
	while (left[i] && left[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (left[i] && left[i] != '\n')
	{
		str[i] = left[i];
		i++;
	}
	if (left[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

static char	*joinex(char *buffer, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, buf);
	free(buffer);
	return (tmp);
}

static char	*readex(int fd, char *res)
{
	char	*buffer;
	size_t	bytes_read;

	if (!res)
		res = malloc((ft_strlen(res) + 1) * sizeof(char));
	if (!res)
		return (0);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(res);
		return (0);
	}
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		res[bytes_read] = 0;
		res = joinex(res, buffer);
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	buffer = malloc(BUFFER_SIZE + 2);
	if (buffer == NULL || fd < 0 || BUFFER_SIZE < 0)
		return (0);
	//read(fd, line, BUFFER_SIZE);
	line = linex(line);
	printf("line: %s end ", buffer);
	line = readex(fd, buffer);
	if (!line)
		return (0);
	return (line);
}

int	main(void)
{
	char		*line;
	int	i;
	int	fd1;

	fd1 = open("test.txt", O_RDONLY);
	i = 0;
	while (i < 10)
	{
		line = get_next_line(fd1);
	//	printf("line [%02d]: %s", i, line);
		//free(line);
		i++;
	}
	close(fd1);
}
/*
static char	*readex(int fd, char *res)
{
	char	*buffer;
	size_t	bytes_read;

	if (!res)
		res = malloc((ft_strlen(res) + 1) * sizeof(char));
	if (!res)
		return (0);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(res);
		return (0);
	}
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, res, BUFFER_SIZE);
		buffer[bytes_read] = 0;
		res = freeex(res, buffer);
		if (ft_strchr(res, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}
static char	*readex(int fd, char *res)
{
	char	*ptr;
	size_t	bytes_read;
	int	i;
	printf("in readex");
	i = 0;
	if (!res)
		res = malloc((ft_strlen(res) + 1) * sizeof(char));
	if (!res)
		return (0);
	ptr = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (res == 0)
		return (0);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		printf("in bytes read");
		bytes_read = read(fd, res, BUFFER_SIZE);
		if (ft_strchr(res, '\n'))
			break ;
	}
	free(ptr);
	return (res);
}

//fill_line_buffer(int fd, char *left_c, char *buffer)

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (buffer == NULL || fd < 0 || BUFFER_SIZE < 0)
		return (0);
	buffer = readex(fd, buffer);
	printf("%s test ", buffer);
	if (!buffer)
		return (0);
	return (line);
}
char	*get_next_line(int fd)
{
	static char	*reminder;
	char		*buf;
	char		*line;
	char		*newline;

	reminder = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL || fd < 0)
		return (0);
	while (read(fd, buf, BUFFER_SIZE) > 0)
	{
		buf[BUFFER_SIZE] = '\0';
		newline = ft_strchr(buf, '\n');
		if (newline != NULL)
		{
			*newline = '\0';
			reminder = ft_strdup(newline + 1);
		}
		if (reminder == NULL)
		{
			line = ft_strjoin(reminder, buf);
			free(reminder);
			reminder = NULL;
		}
		else
			line = ft_strdup(buf);
		if (line == NULL)
			return (0);
		printf("%s\n", line);
		free(line);
	}
	free(buf);
	return (0);
}
char	*is_line(const char *lbuf)
{
	int	i;
	char	j;
	char		*tmp;
printf("3");
	tmp = malloc((ft_strlen(lbuf) + 1) * sizeof(char));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	j = *ft_strchr(lbuf, '\n');
	//printf("%s", j);
	while (lbuf[i] != '\0')
	{
		printf("2");
		while (lbuf[i] != lbuf[j])
		{
			tmp[i] = lbuf[i];
			printf("1");
			printf("%s", tmp);
		}
		i++;
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*reminder;
	char		*line;
	char		*buf;

	buf = malloc(BUFFER_SIZE + 1);
	reminder = malloc(BUFFER_SIZE + 1);
	if (buf == NULL || fd < 0)
		return (0);
	while (read(fd, buf, BUFFER_SIZE))
	{
		reminder = ft_strjoin(reminder, buf);
		is_line(buf);
		printf("%s", reminder);
	}
	free(buf);
	return (0);
}
*/