/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:54:03 by clement           #+#    #+#             */
/*   Updated: 2023/10/13 13:06:48 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

size_t	ft_lengh_array(char **array)
{
	size_t	x;

	if (!array)
		return (0);
	x = 0;
	while (array[x])
		x++;
	return (x);
}

void	ft_free_array(char **array)
{
	int	i;
	int	j;

	if (array)
	{
		j = ft_lengh_array(array);
		i = 0;
		while (i < j)
			free(array[i++]);
		free(array);
	}
}
