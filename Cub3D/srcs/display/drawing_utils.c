/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:13:43 by hdupuy            #+#    #+#             */
/*   Updated: 2023/12/19 09:38:41 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_dot(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			my_mlx_pixel_put(data, x + i, y + j, data->game.color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_data *data)
{
	int	x;
	int	y;

	x = data->game.ray.pos_x * data->game.maps - data->game.square_size / 4;
	y = data->game.ray.pos_y * data->game.maps - data->game.square_size / 4;
	data->game.color = 0x00FF00;
	draw_square(data, x, y, data->game.square_size / 2);
}

void	draw_square(t_data *data, int x, int y, int side)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < side)
	{
		j = 0;
		while (j < side)
		{
			my_mlx_pixel_put(data, x + i, y + j, data->game.color);
			j++;
		}
		i++;
	}
}

void	drawbackground(t_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 1920)
	{
		j = 0;
		while (j < 1080)
		{
			if (j < 1080 / 2)
				my_mlx_pixel_put(data, x + i, y + j,
					darken_color(data->game.ceiling_color, j));
			else
				my_mlx_pixel_put(data, x + i, y + j, data->game.floor_color);
			j++;
		}
		i++;
	}
}
