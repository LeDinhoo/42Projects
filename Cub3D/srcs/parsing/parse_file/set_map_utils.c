/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:59:10 by clement           #+#    #+#             */
/*   Updated: 2023/12/20 13:21:27 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

void	ft_copy_map(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	map->copy_map = ft_calloc((map->height + 1), sizeof(char *));
	while (y < map->height)
	{
		map->copy_map[y] = ft_calloc((map->width + 1), sizeof(char));
		x = 0;
		while (map->map[y][x] && (x < map->width))
		{
			map->copy_map[y][x] = map->map[y][x];
			x++;
		}
		while (x < map->width)
			map->copy_map[y][x++] = ' ';
		map->copy_map[y][x] = '\0';
		y++;
	}
	map->copy_map[y] = NULL;
}

int	ft_check_border(t_map *map)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	(void)*map;
	if (ft_check_border_up(map, x) == -1)
		return (-1);
	x = map->width - 1;
	if (ft_check_border_right(map, y) == -1)
		return (-1);
	x = map->width - 1;
	if (ft_check_border_down(map, x) == -1)
		return (-1);
	y = map->height - 1;
	if (ft_check_border_left(map, y) == -1)
		return (-1);
	return (0);
}

int	ft_check_intern_walls(t_map *map)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	(void)*map;
	while (y < map->height - 1)
	{
		x = 1;
		while (x < map->width - 1)
		{
			if (map->copy_map[y][x] == '0')
			{
				if (map->copy_map[y - 1][x] == ' ' || map->copy_map[y
					+ 1][x] == ' ' || map->copy_map[y][x + 1] == ' '
					|| map->copy_map[y][x - 1] == ' ')
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	ft_check_walls(t_map *map)
{
	(void)*map;
	if (ft_check_border(map) == -1)
		return (-1);
	if (ft_check_intern_walls(map) == -1)
		return (-1);
	return (0);
}

void	ft_free_map(char **map)
{
	ssize_t	index;

	index = 0;
	if (!map)
		return ;
	while (map && map[index])
	{
		free(map[index]);
		index++;
	}
	free(map);
}

/*
int	ft_check_border(t_map *map)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	(void)	*map;
	while (x < map->width)
	{
		if (map->copy_map[0][x] == '0')
			return (-1);
		else
			x++;
	}
	while (y < map->height)
	{
		if (map->copy_map[y][map->width - 1] == '0')
			return (-1);
		else
			y++;
	}
	x = map->width - 1;
	while (x > 0)
	{
		if (map->copy_map[map->height - 1][x] == '0')
			return (-1);
		else
			x--;
	}
	y = map->height - 1;
	while (y > 0)
	{
		if (map->copy_map[y][0] == '0')
			return (-1);
		else
			y--;
	}
	return (0);
}
*/
