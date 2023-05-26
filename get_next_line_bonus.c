/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sallorca <sallorca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:56:10 by sallorca          #+#    #+#             */
/*   Updated: 2023/02/16 12:27:59 by sallorca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

/* READ AND COPY, OR JOIN. There's need to create a backup with space in memory 
 * for: BUFFER_SIZE + 1.
 * Then, let's check if there's a '\n' in our static, if we have readed before.
 * With de "read" function, we save the amount of bytes readed by it in our 
 * read_bytes, to check if there's any errors in the text or lecture.
 * After we read, the function keeps in our backup the lines that it reads.
 * So now, we need to update the static, if needed joining it with (ft_strjoin) 
 * with the content of the new backup.
 * Once the static is updated, now we can free my backup(tmp), for the next time 
 * if we need to read more.
 * */
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

/*Creamos una nueva copia de seguridad donde alojar nuestro string(*str)
 * Chequeamos si el primer elemento de nuestra estática es nulo.
 * Realizamos el bucle while para encontrar el final de la línea.
 * Asignamos memoria a nuestra nueva copia de seguridad.
 * Chequeamos si el puntero es nulo.
 * Reiniciamos la variable a 0.
 * Copiamos los caracteres de nuestra estática en nuestra copia(str) hasta
 * el final de linea.
 * Si encontramos un salto de linea, copiamos ese tambien en nuestra copia.
 * Finalmente devolvemos el pountero de la nueva cadela de caracteres.
 */
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

/* Creamos una nueva copia de seguridad(next).
 * Bucle while que recorre nuestra estática(read_str[i]) hasta encontrar 
 * el caracter nulo o fin de linea, incrementando la i.
 * Si se llega al final de la cadena sin encontrar un carácter de nueva línea,
 * significa que no hay más líneas que leer, por lo que se libera la memoria
 * reservada para read_str con la función free y se devuelve un puntero(NULL).
 * Si se encuentra un carácter de nueva línea, se reserva memoria con ft_calloc
 * para mi copia de seguridad(next), que contendrá la siguiente línea de
 * read_str.
 * El tamaño de next será la longitud de read_str menos la posición del carácter
 * de nueva línea más uno (para incluir el carácter nulo que finaliza la cadena).
 * Si la reserva de memoria no se pudo realizar, se devuelve un puntero nulo.
 * Se incrementa el valor de i para apuntar al carácter siguiente al carácter
 * de nueva línea en read_str.
 * Se entra en otro bucle while que recorre el resto de la cadena read_str a 
 * partir de la posición i y copia cada carácter en next, 
 * incrementando el valor de j en cada iteración.
 * Cuando se han copiado todos los caracteres de read_str en next, se añad un
 * carácter nulo al final de next.
 * Se libera la memoria reservada para read_str con la función free.
 * Se devuelve el puntero a la cadena next, que contiene la siguiente 
 * línea de read_str.
*/
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

/* Le pasamos un fd, del cual nos devuelve una línea.
 * Empezamos con la estructura de control con la que chequeamos el fd, B_S y O_M.
 * Chequeamos que mi estática tenga info y le reservamos memoria.
 * Con la función ft_read, implementamos nuestra estática.
 * Si nuestra estática no tiene contenido, retorna NULL.
 * Line la igualamos a lo que la función get_line.
 * En nuestra estática la igualamos a lo conseguido con next_line.
 * Finalmente nos devuelva el contenido de line, que serra la linea leida.
 * */
char	*get_next_line(int fd)
{
	char		*line;
	static char	*read_str[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	if (!read_str[fd])
		read_str[fd] = ft_calloc(1, 1);
	read_str[fd] = ft_read(fd, read_str[fd]);
	if (!read_str[fd])
		return (NULL);
	line = ft_get_line(read_str[fd]);
	read_str[fd] = ft_next_line(read_str[fd]);
	return (line);
}
/*
int   main(void)
{
    char    *line;
    int     i;
    int     fd1;
    int     fd2;
    int     fd3;
    fd1 = open("texto.txt", O_RDONLY);
    fd2 = open("texto2.txt", O_RDONLY);
    fd3 = open("texto3.txt", O_RDONLY);
    i = 1;
    while (i < 6)
    {
        line = get_next_line(fd1);
        printf("line %d: %s", i, line);
        free(line);
        line = get_next_line(fd2);
        printf("line %d: %s", i, line);
        free(line);
        line = get_next_line(fd3);
        printf("line %d: %s", i, line);
        free(line);
        i++;
    }
    close(fd1);
    close(fd2);
    close(fd3);
    return (0);
}*/
