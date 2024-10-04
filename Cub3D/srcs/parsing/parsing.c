/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:50:05 by clement           #+#    #+#             */
/*   Updated: 2023/12/20 13:24:06 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	find_pos(char **map, int *i, int *j)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				*i = x;
				*j = y;
				return (0);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (-1);
}

void	dup_map(t_data *data)
{
	char	**new_map;
	int		i;

	new_map = ft_calloc((data->map.height + 1), sizeof(char *));
	i = 0;
	while (i < data->map.height)
	{
		new_map[i] = ft_strdup(data->map.map[i]);
		i++;
	}
	new_map[i] = NULL;
	data->map.copy_map = new_map;
}

int	is_one_player(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (map[j])
	{
		while (map[j][i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'E'
				|| map[j][i] == 'W')
				count++;
			i++;
		}
		i = 0;
		j++;
	}
	if (count == 1)
		return (0);
	return (-1);
}

void	ft_parsing(char *file, t_data *data)
{
	int	fd;
	int	i;
	int	j;

	fd = open(file, __O_DIRECTORY);
	if (fd != -1)
		ft_error(data, "Invalid: is a directory", NULL);
	data->fd1 = open(file, O_RDONLY);
	if (data->fd1 == -1)
		ft_error(data, "Invalid file '.cub'", NULL);
	ft_parse_file(data, data->fd1);
	data->map.width = find_max_width(data->map.map);
	find_pos(data->map.map, &i, &j);
	ft_copy_map(&data->map);
	if (is_map_valid(data->map.map) == -1)
		ft_error(data, "Invalid character", NULL);
	if (is_one_player(data->map.map) == -1)
		ft_error(data, "Invalid number of player", NULL);
	if (ft_check_walls(&data->map) == -1)
		ft_error(data, "Border not ok", NULL);
	if (diffusion_algorithm(data->map.map, i, j, data) == -1)
		ft_error(data, "Invalid path", NULL);
	switch_space(data->map.copy_map);
	data->map.good_map = data->map.copy_map;
	close(data->fd1);
}

int	ft_cub(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '.')
	{
		i--;
		if (i == 0)
		{
			ft_error(data, "Invalid map name", NULL);
			return (0);
		}
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
		ft_parsing(str, data);
	else
		ft_error(data, "Invalid map name", NULL);
	return (0);
}
