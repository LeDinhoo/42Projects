/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:37:47 by hdupuy            #+#    #+#             */
/*   Updated: 2023/12/19 09:44:23 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	minimap_background(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			my_mlx_pixel_put(data, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

void	init_minimap(t_data *data)
{
	data->minimap.mapsize = 64;
	data->minimap.posx = (data->game.ray.pos_x * data->game.maps
			- data->game.square_size / 4);
	data->minimap.posy = (data->game.ray.pos_y * data->game.maps
			- data->game.square_size / 4);
	data->minimap.posx = data->minimap.posx - 32;
	data->minimap.posy = data->minimap.posy - 32;
	if (data->minimap.posx < 0)
		data->minimap.posx = 0;
	if (data->minimap.posy < 0)
		data->minimap.posy = 0;
}

void	minimap_floor(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->minimap.mapsize)
	{
		j = 0;
		while (j < data->minimap.mapsize)
		{
			if (!data->map.good_map[(data->minimap.posy + i) / 16])
				break ;
			if (data->map.good_map[(data->minimap.posy + i) / 16]
				[(data->minimap.posx + j) / 16] != '1')
			{
				data->game.color = 0x555555;
				my_mlx_pixel_put(data, j, i, data->game.color);
			}
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	init_minimap(data);
	minimap_background(data);
	minimap_floor(data);
	data->game.color = 0x00FF00;
	draw_square(data, 32 - 8, 32 - 8, data->game.square_size);
}
