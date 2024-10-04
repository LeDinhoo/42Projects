/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:24:41 by clement           #+#    #+#             */
/*   Updated: 2023/12/18 12:05:00 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	check_backslash(char *buf, char **to_return);
static ssize_t	loop_read(int fd, char *buf, char **to_return);

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*to_return;
	ssize_t		check_ret_value;

	if (fd < 0 || read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0)
	{
		buf[0] = 0;
		return (NULL);
	}
	to_return = malloc(sizeof(char));
	if (to_return == 0)
		return (NULL);
	to_return[0] = '\0';
	if (ft_strlen(buf) != 0)
	{
		check_ret_value = check_backslash(buf, &to_return);
		if (check_ret_value == -1)
			return (NULL);
		if (check_ret_value == 1)
			return (to_return);
	}
	if (loop_read(fd, buf, &to_return) == -1)
		return (NULL);
	return (to_return);
}

static ssize_t	check_backslash(char *buf, char **to_return)
{
	ssize_t	i;

	i = backslash(buf);
	if (i != -1)
	{
		buf[i] = '\0';
		*to_return = ft_strjoin_bis(*to_return, buf);
		if (*to_return == NULL)
			return (-1);
		setup_buf(buf, i);
		return (1);
	}
	*to_return = ft_strjoin_bis(*to_return, buf);
	if (*to_return == NULL)
		return (-1);
	return (0);
}

static ssize_t	loop_read(int fd, char *buf, char **to_return)
{
	ssize_t		read_value;
	ssize_t		check_ret_value;

	read_value = read(fd, buf, BUFFER_SIZE);
	if (read_value == -1 || (read_value == 0 && ft_strlen(buf) == 0))
		return (free(*to_return), -1);
	buf[read_value] = '\0';
	while (read_value)
	{
		check_ret_value = check_backslash(buf, to_return);
		if (check_ret_value == -1 || check_ret_value == 1)
			return (read_value);
		read_value = read(fd, buf, BUFFER_SIZE);
		if (read_value == -1)
		{
			free(*to_return);
			return (-1);
		}
		buf[read_value] = '\0';
		if (read_value == 0)
			return (1);
	}
	buf[0] = 0;
	return (0);
}
