/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sallorca <sallorca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:56:10 by sallorca          #+#    #+#             */
/*   Updated: 2023/02/08 12:56:20 by sallorca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*ft_read(int fd, char *read_str)
{
	char	*tmp;
	int		read_bytes;

	tmp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	read_bytes = 1;
	while (read_bytes != 0 && !(ft_strchr(read_str, '\n')))
	{
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(tmp);
			free(read_str);
			return (NULL);
		}
		tmp[read_bytes] = '\0';
		read_str = ft_strjoin(read_str, tmp);
	}
	free(tmp);
	return (read_str);
}

char	*ft_get_line(char *read_str)
{
	int		i;
	char	*str;

	i = 0;
	if (!read_str[i])
		return (NULL);
	while (read_str[i] != '\0' && read_str[i] != '\n')
		i++;
	str = ft_calloc(i + 2, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (read_str[i] != '\0' && read_str[i] != '\n')
	{
		str[i] = read_str[i];
		i++;
	}
	if (read_str[i] == '\n')
	{
		str[i] = read_str[i];
		i++;
	}
	return (str);
}

char	*ft_next_line(char *read_str)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	while (read_str[i] != '\0' && read_str[i] != '\n')
		i++;
	if (!read_str[i])
	{
		free(read_str);
		return (NULL);
	}
	next = ft_calloc((ft_strlen(read_str) - i + 1), sizeof(char));
	if (!next)
		return (NULL);
	i++;
	j = 0;
	while (read_str[i])
		next[j++] = read_str[i++];
	next[j] = '\0';
	free(read_str);
	return (next);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*read_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_str)
		read_str = ft_calloc(1, 1);
	read_str = ft_read(fd, read_str);
	if (!read_str)
		return (NULL);
	line = ft_get_line(read_str);
	read_str = ft_next_line(read_str);
	return (line);
}
/*int	main(void)
{
	char	*line;
	int		fd;
	fd = open("texto.txt", O_RDONLY);
	if (fd == -1)
	{
		perror ("open");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	printf("%s\n", line);
	close(fd);
	return (0);
}*/
