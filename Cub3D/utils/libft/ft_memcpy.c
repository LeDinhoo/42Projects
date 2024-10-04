/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:06:30 by cbacquet          #+#    #+#             */
/*   Updated: 2022/11/24 16:41:37 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (dst == NULL && src == NULL)
		return (dst);
	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
/*
int main(void)
{
    unsigned char src[] = "Hello";
    unsigned char dst [13];

    memcpy(dst, src, 6);
    printf("dst after first memcpy() = %s\n", dst);

    memcpy(dst + sizeof(src)-1, " world", 8);
    printf("dst after second memcpy() = %s\n", dst);

    ft_memcpy(dst, src, 6);
    printf ("dst after first ft_memcpy = %s\n", dst);

    ft_memcpy(dst + sizeof (src) - 1, "world", 8);
    printf("dst after second ft_memcpy = %s\n", dst);

    return 0;
}
*/
