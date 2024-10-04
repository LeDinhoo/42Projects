/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:25:27 by clement           #+#    #+#             */
/*   Updated: 2023/11/06 11:30:07 by clement          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	backslash(char *buf)
{
	size_t	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin_bis(char *s1, char *s2)
{
	char	*mem;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	mem = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!mem)
		return (free(s1), NULL);
	i = 0;
	while (s1[i])
	{
		mem[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (s2[i])
	{
		mem[j] = s2[i];
		i++;
		j++;
	}
	mem[j] = '\0';
	return (free(s1), mem);
}

void	setup_buf(char *buf, size_t i)
{
	size_t	j;

	j = 0;
	i++;
	while (buf[i] && i < BUFFER_SIZE)
	{
		buf[j] = buf[i];
		i++;
		j++;
	}
	buf[j] = '\0';
}
