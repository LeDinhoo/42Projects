/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:37:31 by clement           #+#    #+#             */
/*   Updated: 2023/12/15 16:09:42 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

int	ft_size_map(t_map *map, int fd)
{
	char	*line;

	line = ft_go_top_map(fd);
	while (line && ft_same_str(line, ""))
		line = get_next_line(fd);
	while (line && !ft_same_str(line, ""))
	{
		if ((int)ft_strlen(line) > map->width)
			map->width = ft_strlen(line);
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		if (ft_same_str(line, ""))
			return (printf("Error\nmap error\n"), free(line), -1);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	ft_save_map(t_map *map, char *file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	map->map = ft_calloc((map->height + 1), sizeof(char *));
	line = ft_go_top_map(fd);
	while (line)
	{
		map->map[i] = ft_strdup(line);
		free(line);
		if (map->map[i] == NULL)
		{
			ft_free_map(map->map);
			return ;
		}
		i++;
		line = get_next_line(fd);
	}
}

int	ft_check_map(t_map *map, int fd, t_data *data)
{
	if (ft_map_elem(map, fd, data) == -1)
		return (-1);
	if (ft_check_walls(map) == -1)
		return (printf("Error\nwalls are not ok\n"), -1);
	return (0);
}

void	ft_edit_good_map(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	map->good_map = NULL;
	map->good_map = ft_calloc((map->height + 1), sizeof(char *));
	while (y < map->height)
	{
		map->good_map[y] = ft_calloc((map->width + 1), sizeof(char));
		x = 0;
		while (map->copy_map[y][x] && x < map->width)
		{
			if (map->copy_map[y][x] == ' ' || map->copy_map[y][x] == '\0')
				map->good_map[y][x] = '1';
			else
				map->good_map[y][x] = map->copy_map[y][x];
			x++;
		}
		map->good_map[y][x] = '\0';
		y++;
	}
	map->good_map[y] = NULL;
}

void	ft_set_map(char *file, t_data *data, int fd)
{
	close(fd);
	fd = open(file, O_RDONLY);
	if (ft_size_map(&data->map, fd) == -1)
		return (close(fd), ft_end_set_map(data), (void) -1);
	ft_save_map(&data->map, file);
	if (ft_check_map(&data->map, fd, data) == 0)
		ft_edit_good_map(&data->map);
	else
		return (printf("Error\nmap is not good\n"),
			close(fd), ft_pre_end(data), (void) -1);
	ft_check_perso(&data->map, &data->player);
}
