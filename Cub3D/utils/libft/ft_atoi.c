/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:36:49 by cbacquet          #+#    #+#             */
/*   Updated: 2022/12/06 12:02:53 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_overflow(int sign)
{
	if (sign < 0)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result != ((result * 10 + (*str - '0')) / 10))
			return ((int) ft_overflow(sign));
		result = result * 10 + *str - '0';
		str++;
	}
	return ((int) result * sign);
}

/*
#include <limits.h>

int main(void)
{
	// char buffer[10000];
	// sprintf(buffer, "%zu", ((long)INT_MAX) + 1);
    //char str[]="4294967299";
	char s[] = "18446744073709551616";
	//char s1[] = "2147483647";

    printf("%d\n", ft_atoi(s));
	printf("%d\n", atoi(s));
    return 0;
}
*/