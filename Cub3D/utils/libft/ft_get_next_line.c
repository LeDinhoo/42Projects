/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:12:37 by clement           #+#    #+#             */
/*   Updated: 2023/10/26 15:38:03 by clement          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "libft.h"
#include <limits.h>

char	*final_read(char buf[BUFFER_SIZE + 1], int reading, char *str)
{
	move_buf(buf, BUFFER_SIZE);
	if (reading < 0)
	{
		if (str)
			free (str);
		return (NULL);
	}
	return (str);
}

char	*joined(char buf[BUFFER_SIZE + 1], char *str)
{
	str = gnl_join(str, buf, index_of(buf, '\n') + 1);
	if (str)
		move_buf(buf, index_of(buf, '\n') + 1);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buf[_SC_OPEN_MAX][BUFFER_SIZE + 1];
	char		*str;
	int			reading;

	if (fd == -1 || fd > _SC_OPEN_MAX)
		return (NULL);
	reading = 1;
	str = NULL;
	while (reading > 0)
	{
		if (index_of(buf[fd], '\n') != -1)
			return (joined(buf[fd], str));
		if (buf[fd][0])
		{
			str = gnl_join(str, buf[fd], ft_strlen(buf[fd]));
			if (!str)
				return (NULL);
			move_buf(buf[fd], BUFFER_SIZE);
		}
		reading = read(fd, buf[fd], BUFFER_SIZE);
	}
	if (reading <= 0)
		return (final_read(buf[fd], reading, str));
	free (str);
	return (NULL);
}*/
