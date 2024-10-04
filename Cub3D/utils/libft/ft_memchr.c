/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:05:56 by cbacquet          #+#    #+#             */
/*   Updated: 2022/12/05 11:11:45 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char)(c))
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
/*
int main (void)
{
	printf("%s\n", memchr("bonjour", 'j', 6));
	printf("%s\n", ft_memchr("bonjour", 'j', 6));
}
*/
