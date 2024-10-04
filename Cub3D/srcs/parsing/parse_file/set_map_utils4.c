/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:33:43 by cbacquet          #+#    #+#             */
/*   Updated: 2023/12/19 18:02:05 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

int	ft_check_border_up(t_map *map, int x)
{
	while (x < map->width)
	{
		if (map->copy_map[0][x] == '0')
			return (-1);
		else
			x++;
	}
	return (0);
}

int	ft_check_border_right(t_map *map, int y)
{
	while (y < map->height)
	{
		if (map->copy_map[y][map->width - 1] == '0')
			return (-1);
		else
			y++;
	}
	return (0);
}

int	ft_check_border_down(t_map *map, int x)
{
	while (x > 0)
	{
		if (map->copy_map[map->height - 1][x] == '0')
			return (-1);
		else
			x--;
	}
	return (0);
}

int	ft_check_border_left(t_map *map, int y)
{
	while (y > 0)
	{
		if (map->copy_map[y][0] == '0')
			return (-1);
		else
			y--;
	}
	return (0);
}
