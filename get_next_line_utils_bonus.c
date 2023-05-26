/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sallorca <sallorca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:01:40 by sallorca          #+#    #+#             */
/*   Updated: 2023/02/08 13:01:11 by sallorca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char	*s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
	{
		len++;
	}
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;

	i = 0;
	mem = malloc(count * size);
	if (mem == 0)
		return (0);
	while (i < count * size)
	{
		mem [i] = 0;
		i++;
	}
	return (mem);
}

char	*ft_strjoin(char *read_str, char *tmp)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!read_str || !tmp)
		return (NULL);
	str = ft_calloc(ft_strlen(read_str) + ft_strlen(tmp) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (read_str[i] != '\0')
	{
		str[i] = read_str[i];
		i++;
	}
	while (tmp[j] != '\0')
		str[i++] = tmp[j++];
	free(read_str);
	return (str);
}
