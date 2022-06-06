/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ren-nasr <ren-nasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:57:16 by ren-nasr          #+#    #+#             */
/*   Updated: 2022/06/03 09:33:01 by ren-nasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	index_line(const char *s, int c)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (p[i])
	{
		if (p[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static void	get_rest(char **save, char **line, ssize_t eof, char **tmp)
{
	if (eof == 0 && !ft_strchr(*save, '\n'))
	{
		*line = ft_strdup(*save);
		*save = 0;
	}
	else
	{
		*line = ft_substr(*save, 0, index_line(*save, '\n') + 1);
		*save = ft_strdup(*save + index_line(*save, '\n') + 1);
	}
	free(*tmp);
	if (**line == '\0')
	{
		free(*line);
		*line = NULL;
	}
}

static void	get_line(int fd, char **save, char *buff, char **line)
{
	ssize_t	eof;
	char	*tmp;

	eof = 1;
	buff[0] = '\0';
	while (eof != 0 && (!ft_strchr(buff, '\n')))
	{
		eof = read(fd, buff, BUFFER_SIZE);
		buff[eof] = '\0';
		tmp = *save;
		*save = ft_strjoin(tmp, buff);
		free(tmp);
	}
	free(buff);
	tmp = *save;
	get_rest(save, line, eof, &tmp);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buff;
	char		*line;

	buff = NULL;
	if (read(fd, buff, 0) != 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	if (!save)
		save = ft_strdup("");
	get_line(fd, &save, buff, &line);
	return (line);
}

// #include <fcntl.h>

// int	main()
// {
// 	int	fd = open("foo.txt", O_RDONLY);
// 	int i = 0;
// 	while (i < 2)
// 	{
// 		printf("%s", get_next_line(fd));
// 		i++;
// 	}
// 	// while (line)
// 	// {
// 	// 	printf("line : %s|", line);
// 	// 	free(line);
// 	// 	line = get_next_line(fd);
// 	// }
// 	// free(line);
// 	// //while (1);
// 	return (0);
// }