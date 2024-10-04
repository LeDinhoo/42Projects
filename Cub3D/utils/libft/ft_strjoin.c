/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:54:11 by cbacquet          #+#    #+#             */
/*   Updated: 2022/12/05 12:25:25 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	size;
	char	*str;

	if (!s1)
		return (NULL);
	str = (char *)(malloc)(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2)+ 1));
	if (!str)
		return (NULL);
	i = 0;
	size = 0;
	while (s1[i])
		str[size++] = s1[i++];
	i = 0;
	while (s2[i])
		str[size++] = s2[i++];
	str[size] = '\0';
	return (str);
}
/*
int main(void)
{		
	char s1[] = "Hello";
	char s2[] = " there";
	
	printf("%s\n", ft_strjoin(s1, s2));
}
*/