/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gabriel.bazart@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:20:44 by gbazart           #+#    #+#             */
/*   Updated: 2024/01/11 16:52:01 by gbazart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_sub(char **rest, char **line)
{
	char	*str;

	str = NULL;
	if (*rest)
	{
		*line = *rest;
		str = ft_strchr(*rest, '\n');
		if (str)
		{
			str++;
			if (*str != '\0')
				*rest = ft_strdup(str);
			else
				*rest = NULL;
			*str = '\0';
		}
		else
			*rest = NULL;
	}
	else
	{
		*line = (char *)malloc(sizeof(char) * 1);
		*line[0] = '\0';
	}
	return (str);
}

char	*ft_sub_2(char **rest, char **line, char **buf)
{
	char	*str;
	char	*tmp;

	str = ft_strchr(*buf, '\n');
	if (str)
	{
		str++;
		if (*str != '\0')
			*rest = ft_strdup(str);
		*str = '\0';
	}
	tmp = *line;
	*line = ft_strjoin(*line, *buf);
	free(tmp);
	return (str);
}

/**
 * @brief Get the next line from a file
 * descriptor and free static variable
 * when we reach the end of the file.
 *
 * @param fd (int) file descriptor
 * @return (char *) don't forget to free it.
 */
char	*get_next_line(int fd)
{
	char		*buf;
	int			i;
	char		*str;
	static char	*rest[1024];
	char		*line;

	if (BUFFER_SIZE < 1 || read(fd, 0, 0) == -1 || fd < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	str = ft_sub(&rest[fd], &line);
	i = 1;
	while (!str && i)
	{
		i = read(fd, buf, BUFFER_SIZE);
		buf[i] = '\0';
		str = ft_sub_2(&rest[fd], &line, &buf);
	}
	free(buf);
	if (ft_strlen(line) > 0)
		return (line);
	free(line);
	return (NULL);
}
