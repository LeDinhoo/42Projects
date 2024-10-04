/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:06:59 by cbacquet          #+#    #+#             */
/*   Updated: 2022/11/11 17:33:50 by cbacquet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(unsigned char *)(b + i) = c;
		i++;
	}
	return (b);
}
/*
int main (void)
{
    int test[2];
    int tab[2];

    //memset(test, -1, sizeof(test));
    //printf("%d %d\n", test[0], test[1]);

    ft_memset(tab, -2, sizeof(tab));
    printf("%d %d\n", tab[0], tab[1]);

    return 0;
}
*/
