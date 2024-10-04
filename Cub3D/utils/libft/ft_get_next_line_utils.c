/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:12:56 by clement           #+#    #+#             */
/*   Updated: 2023/10/26 15:38:11 by clement          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	index_of(char buf[BUFFER_SIZE +1], char r)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == r)
			return (i);
		i++;
	}
	return (-1);
}

char	*gnl_join(char *str, char buff[BUFFER_SIZE + 1], size_t	len)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(sizeof(char) * (ft_strlen(str) + len + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	if (str)
	{
		while (str[i])
		{
			result[i] = str[i];
			i++;
		}
	}
	while (len--)
		result[i++] = buff[j++];
	result[i] = '\0';
	if (str)
		free (str);
	return (result);
}

void	move_buf(char buf[BUFFER_SIZE + 1], size_t index)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = ft_strlen(buf);
	while (buf[x])
	{
		if (x + index < y)
			buf[x] = buf[x + index];
		else
			buf[x] = '\0';
		x++;
	}
}*/
