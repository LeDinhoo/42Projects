/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:03:21 by cbacquet          #+#    #+#             */
/*   Updated: 2022/11/24 16:12:38 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = 0;
		i++;
	}
}
/*
int main (void)
{
    char str[50] = "GeeksforGeeks is for programming geeks.";
    printf("\nBefore bzero() : %s\n", str);

    ft_bzero(str + 16, 20*sizeof(char));

    printf("After bzero() : %s", str);
}
*/
