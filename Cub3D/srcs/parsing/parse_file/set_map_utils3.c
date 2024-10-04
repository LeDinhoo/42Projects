/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:43:35 by hdupuy            #+#    #+#             */
/*   Updated: 2023/12/13 17:38:17 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

int	check_if_only_good_elem(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '\t')
				return (printf("Error\nmap's element not valid\n"), -1);
			if (map->map[y][x] != '1' && map->map[y][x] != '0'
				&& map->map[y][x] != 'N' && map->map[y][x] != 'S'
				&& map->map[y][x] != 'W' && map->map[y][x] != 'E'
				&& map->map[y][x] != ' ')
				return (printf("Error\nmap's element not valid\n"), -1);
			x++;
		}
		y++;
	}
	return (0);
}

int	ft_player_good_pos(t_map *map, int y, int x)
{
	if ((map->map[y - 1][x] == '1' || map->map[y - 1][x] == ' ') &&
		(map->map[y + 1][x] == '1' || map->map[y + 1][x] == ' ') &&
		(map->map[y][x + 1] == '1' || map->map[y][x + 1] == ' ') &&
		(map->map[y][x - 1] == '1' || map->map[y][x - 1] == ' '))
		return (-1);
	return (0);
}

int	check_player_are_only(t_map *map)
{
	int	x;
	int	y;
	int	nb_player;

	y = 0;
	x = 0;
	nb_player = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x++])
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
				|| map->map[y][x] == 'W' || map->map[y][x] == 'E')
			{
				if (ft_player_good_pos(map, y, x) == -1)
					return (printf("Error\nerror about player\n"), -1);
				nb_player++;
			}
		}
		y++;
	}
	if (nb_player != 1)
		return (printf("Error\nmap's element not valid\n"), -1);
	return (0);
}

void	ft_end_map_elem(t_data *data)
{
	free(data->no);
	free(data->so);
	free(data->ea);
	free(data->we);
	free(data->f);
	free(data->c);
	exit(1);
}

int	ft_map_elem(t_map *map, int fd, t_data *data)
{
	(void)	*map;
	if (check_if_only_good_elem(map) == -1)
		return (ft_free_map(map->map), close(fd), ft_end_map_elem(data), -1);
	if (check_player_are_only(map) == -1)
		return (-1);
	return (0);
}
