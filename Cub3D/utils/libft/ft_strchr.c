/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:07:25 by cbacquet          #+#    #+#             */
/*   Updated: 2023/12/18 11:59:28 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)(c))
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)(c))
		return ((char *)(s + i));
	return (NULL);
}
/*
int main(void)
{
    char test[] = "here i am in 42";
    printf("%s", ft_strchr(test, 'i'));
}
*/
