/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:06:13 by cbacquet          #+#    #+#             */
/*   Updated: 2022/12/05 12:09:14 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	n--;
	while (*(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i) && i < n)
		i++;
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}

/*
int main ()
{

    char s1[15];
    char s2[15];
    int ret;
    int ret2;
    
    memcpy(s1, "hello", 6);
    memcpy(s2, "hello", 6);

    ret = memcmp(s1, s2, 5);
    ret2 = ft_memcmp(s1, s2, 5);

    printf("memcmp : \n");
    if (ret > 0)
        printf("s2 is less than s1");
    else if (ret < 0)
        printf("s1 is less than s2");
    else
        printf("s1 is equal to s2");
    printf("\n");
    printf("ft_memcmp : \n");
    if (ret2 > 0)
        printf("s2 is less than s1");
    else if (ret2 < 0)
        printf("s1 is less than s2");
    else
        printf("s1 is equal to s2");
    
    return 0;
}
*/