/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:06:45 by cbacquet          #+#    #+#             */
/*   Updated: 2022/12/05 12:18:04 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int				i;

	if (!src && !dst)
		return (NULL);
	if (dst > src)
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)len)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	return (dst);
}

/*
int main (void)
{
	char s[50] = "123";
	
	printf("%s\n", memmove(s + 1, s, 4));
	printf("%s\n", ft_memmove(s + 1, s, 4));
}

int main(void)
{
    unsigned char src[] = "Hello";
	unsigned char temp[4096];
    unsigned char dst [13];

    memmove(dst, src, 6);
    printf("dst after first memmove() = %s\n", dst);

    memmove(dst + sizeof(src)-1, " world", 8);
    printf("dst after second memmove() = %s\n", dst);

    ft_memmove(dst, src, 6);
    printf ("dst after first ft_memmove = %s\n", dst);

    ft_memmove(dst + sizeof(src)-1, " world", 8);
    printf("dst after second ft_memmove = %s\n", dst);

    return 0;
}
*/
