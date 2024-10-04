/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:09:05 by cbacquet          #+#    #+#             */
/*   Updated: 2022/11/24 16:56:21 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)(c))
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
/*
int main (void)
{
    char test[] = "here i am in 42";
    printf("%s", ft_strrchr(test, 'i'));
}
*/
