/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:08:53 by cbacquet          #+#    #+#             */
/*   Updated: 2022/12/05 13:24:20 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (len == 0 && !haystack)
		return (NULL);
	if (!*needle)
		return ((char *)(haystack));
	while (i < len && haystack[i])
	{
		j = 0;
		while ((i + j < len) && needle[j] == haystack[i + j] && haystack[i + j])
			j++;
		if (j == ft_strlen(needle))
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
/*
int main (void)
{
	const char *s1;
	const char *s2;
	char *ptr;

	s1 = "lorem ipsum dolor sit amet";
	s2 = "dolor";
	ptr = ft_strnstr(s1, s2, 15);

	printf("%s\n", ptr);
}
*/