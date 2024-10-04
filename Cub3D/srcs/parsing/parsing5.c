/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:58:45 by hdupuy            #+#    #+#             */
/*   Updated: 2023/12/20 13:30:10 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	handle_identifier(t_data *data, char *line)
{
	if (line[data->i] == 'N' && line[data->i + 1] == 'O'
		&& line[data->i + 2] == ' ')
		set_texture1(data, line, NO);
	else if (line[data->i] == 'S' && line[data->i + 1] == 'O'
		&& line[data->i + 2] == ' ')
		set_texture1(data, line, SO);
	else if (line[data->i] == 'W' && line[data->i + 1] == 'E'
		&& line[data->i + 2] == ' ')
		set_texture1(data, line, WE);
	else if (line[data->i] == 'E' && line[data->i + 1] == 'A'
		&& line[data->i + 2] == ' ')
		set_texture1(data, line, EA);
	else if (line[data->i] == 'F' && line[data->i + 1] == ' ')
		set_color1(data, line, F);
	else if (line[data->i] == 'C' && line[data->i + 1] == ' ')
		set_color1(data, line, C);
	else if (line[data->i] != '\0')
		handle_line_map(data, line);
	else if (line[data->i] == '\0' && data->map.height > 0)
		data->empty_line = 1;
}

void	ft_parse_file(t_data *data, int fd)
{
	char	*line;

	data->i = 0;
	data->read = get_next_line(fd);
	data->map.height = 0;
	data->empty_line = 0;
	while (data->read)
	{
		if (settings_full(data) == -1)
			line = ft_strtrim(data->read, " \t");
		else
			line = ft_strdup(data->read);
		handle_identifier(data, line);
		free(line);
		free(data->read);
		data->read = get_next_line(fd);
		data->i = 0;
	}
	if (data->map.height == 0)
		ft_error(data, "Invalid: no map", NULL);
}

int	find_max_width(char **map)
{
	int	i;
	int	max_width;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > (size_t)max_width)
			max_width = ft_strlen(map[i]);
		i++;
	}
	return (max_width);
}

int	is_map_valid(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
				&& map[i][j] != ' ' && map[i][j] != '\t')
				return (-1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	diffusion_algorithm(char **map, int x, int y, t_data *data)
{
	if (x < 0 || y == data->map.height || y < 0
		|| map[y][x] == '\0' || map[y][x] == ' ' || map[y][x] == '\t')
		return (-1);
	if (map[y][x] == '1' || map[y][x] == 'x')
		return (0);
	if (map[y][x] == '0')
		map[y][x] = 'x';
	if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
		|| map[y][x] == 'W')
		map[y][x] = 'x';
	if (diffusion_algorithm(map, x + 1, y, data) == -1)
		return (-1);
	if (diffusion_algorithm(map, x - 1, y, data) == -1)
		return (-1);
	if (diffusion_algorithm(map, x, y + 1, data) == -1)
		return (-1);
	if (diffusion_algorithm(map, x, y - 1, data) == -1)
		return (-1);
	return (0);
}
