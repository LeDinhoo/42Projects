/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:57:11 by hdupuy            #+#    #+#             */
/*   Updated: 2023/12/19 09:58:14 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	set_texture1(t_data *data, char *line, int id)
{
	if (!ft_check_extension(line))
		dup_line(data, line, id);
	else
		ft_error(data, "Invalid texture name", line);
}

void	set_color1(t_data *data, char *line, int id)
{
	if (!check_color(line) && !valid_color(line))
		dup_color(data, line, id);
	else
		ft_error(data, "Invalid color", line);
}

int	settings_full(t_data *data)
{
	if (data->no && data->so && data->we && data->ea && data->f && data->c)
		return (0);
	return (-1);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	add_line_to_map(t_data *data, char *line)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = ft_calloc((data->map.height + 2), sizeof(char *));
	while (i < data->map.height)
	{
		new_map[i] = ft_strdup(data->map.map[i]);
		i++;
	}
	new_map[i] = ft_strdup(line);
	if (data->map.map)
		ft_free_map(data->map.map);
	data->map.map = new_map;
}
