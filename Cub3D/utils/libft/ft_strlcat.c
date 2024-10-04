/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:07:50 by cbacquet          #+#    #+#             */
/*   Updated: 2022/11/18 14:30:03 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;
	size_t	p;

	len_src = ft_strlen(src);
	if (dstsize == 0)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (len_dst >= dstsize)
		return (dstsize + len_src);
	p = len_dst;
	i = 0;
	while (p < dstsize - 1 && src[i])
		dst[p++] = src[i++];
	dst[p] = '\0';
	return (len_src + len_dst);
}
/*
int main (void)
{
	char *dest;
	char *dest2;
	if (!(dest = (char *)malloc(sizeof(*dest) * 15)))
		return (0);
	if (!(dest2 = (char *)malloc(sizeof(*dest) * 15)))
		return (0);
	memset(dest, 0, 15);
	memset(dest, 'r', 6);
	memset(dest2, 0, 15);
	memset(dest2, 'r', 6);
	char src[100] = "lorem ipsum dolor sit amet";

	size_t size = 6;
	
	dest[10] = 'a';
	dest2[10] = 'a';
	printf("Original:\n\t%lu\n\t%s\n", strlcat(dest, src, size), dest);
	printf("ft:\n\t%lu\n\t%s\n", ft_strlcat(dest2, src, size), dest2);
}
*/

/*
size_t len_dst;

len_dst = strlen(dst);
if (len_dst > dstsize)
	return(len_dst + strlen(src));	
return (len_dst + strlcpy(dst + len, src, dstsize - len))
*/