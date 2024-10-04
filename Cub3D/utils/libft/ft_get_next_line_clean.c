/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_clean.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:48:14 by clement           #+#    #+#             */
/*   Updated: 2023/11/06 12:02:01 by clement          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
{
	char	*line = NULL;
	char	buffer[BUFFER_SIZE];
	int		i = 0;
	int		bytes_read;

	while ((bytes_read = read(fd, buffer + i, 1)) > 0)
	{
		if (buffer[i] == '\0')
		{
			line = (char *)malloc(i + 1);
			if (!line)
				return (NULL);
			for (int j = 0; j < i; j++)
				line[j] = buffer[j];
			line[i] = '\0';
			return (line);
		}
		i++;
		if (i >= BUFFER_SIZE)
		{
			line = (char *)malloc(i + 1);
			if (!line)
				return (NULL);
			for (int j = 0; j < i; j++)
				line[j] = buffer[j];
			line[i] = '\0';
			i = 0;
		}
	}

	if (i > 0)
	{
		line = (char *)malloc(i + 1);
		if (!line)
			return (NULL);
		for (int j = 0; j < i; j++)
			line[j] = buffer[j];
		line[i] = '\0';
	}

	return (line);
}*/

/*char	*get_line(int fd, char *line, char *buffer, int i)
{
	int	j;

	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
	while (read(fd, buffer + i, 1) > 0 && buffer[i] != '\n')
		i++;
	if (read(fd, buffer + i, 1) <= 0 && i == 0)
		return (NULL);
	if (buffer[i] != '\n' && i > 0)
		buffer[i++] = '\n';
	line = malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	j = 0;
	if (line != NULL)
	{
		while (j < i)
		{
			if (buffer[j] != '\n')
				line[j] = buffer[j];
			j++;
		}
	}
	line[j] = '\0';
	return (line);
}*/

/*char	*get_line(int fd, char *line, char *buffer, int i)
{
    int j;

    if (line != NULL)
    {
        free(line);
        line = NULL;
    }
    while (read(fd, buffer + i, 1) > 0 && buffer[i] != '\n')
        i++;
    if (i > 0 && buffer[i] == '\n') 
        buffer[i++] = '\n';
    if (read(fd, buffer + i, 1) <= 0 && i == 0)
        return (NULL);
    line = malloc(sizeof(char) * i + 1);
    if (!line)
        return (NULL);
    if (line != NULL)
    {
        j = 0;
        while (j < i)
        {
            if (buffer[j] != '\n')
                line[j] = buffer[j];
            j++;
        }
    }
    line[j] = '\0';
    return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*line;

	line = NULL;
	line = get_line(fd, line, buffer, 0);
	return (line);
}*/
