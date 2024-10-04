/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:04:12 by clement           #+#    #+#             */
/*   Updated: 2023/12/13 19:12:54 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

char	*ft_go_top_map(int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line || (ft_strlen(line) == 0))
	{
		while ((ft_strlen(line) == 0)
			|| ft_isalpha(line[i]) || (line[i] == ' '))
		{
			i = 0;
			if (line[i] == ' ')
			{
				while (line[i] == ' ')
					i++;
				if (line[i] == '1')
					break ;
			}
			free(line);
			line = get_next_line(fd);
		}
		return (line);
	}
	return (NULL);
}

void	ft_set_pos_perso(t_perso *player, char orientation, int x, int y)
{
	player->pos[0] = y;
	player->pos[1] = x;
	if (orientation == 'N')
		player->orientation = 0;
	if (orientation == 'S')
		player->orientation = 180;
	if (orientation == 'W')
		player->orientation = 270;
	if (orientation == 'E')
		player->orientation = 90;
}

void	ft_check_perso(t_map *map, t_perso *player)
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
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
				|| map->map[y][x] == 'W' || map->map[y][x] == 'E')
				ft_set_pos_perso(player, map->map[y][x], x, y);
			x++;
		}
		y++;
	}
}

int	ft_pre_end(t_data *data)
{
	ft_free_map(data->map.map);
	ft_free_map(data->map.copy_map);
	ft_free_images(data);
	free(data->no);
	free(data->so);
	free(data->ea);
	free(data->we);
	free(data->f);
	free(data->c);
	exit(0);
}

int	ft_end_set_map(t_data *data)
{
	ft_free_images(data);
	free(data->no);
	free(data->so);
	free(data->ea);
	free(data->we);
	free(data->f);
	free(data->c);
	exit(0);
}

/*void	ft_print_map(char **map)
{
	int	y;

	y = 0;
	while (map[y])
	{
		printf("%s\n", map[y]);
		y++;
	}
}*/
