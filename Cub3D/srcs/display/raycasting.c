/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:24:38 by hdupuy            #+#    #+#             */
/*   Updated: 2023/11/30 11:52:06 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	perp_wall_dist_and_line_height(t_data *data)
{
	if (data->game.ray.side == 0)
		data->game.ray.perp_wall_dist = (data->game.ray.map_x
				- data->game.ray.pos_x + (1 - data->game.ray.step_x) / 2)
			/ data->game.ray.ray_dir_x;
	else
		data->game.ray.perp_wall_dist = (data->game.ray.map_y
				- data->game.ray.pos_y + (1 - data->game.ray.step_y) / 2)
			/ data->game.ray.ray_dir_y;
	data->game.ray.line_height = (int)(1080 / data->game.ray.perp_wall_dist);
	data->game.ray.draw_start = -data->game.ray.line_height / 2 + 1080 / 2;
	if (data->game.ray.draw_start < 0)
		data->game.ray.draw_start = 0;
	data->game.ray.draw_end = data->game.ray.line_height / 2 + 1080 / 2;
	if (data->game.ray.draw_end >= 1080)
		data->game.ray.draw_end = 1080 - 1;
}

void	calculate_wall_collision(t_data *data)
{
	if (data->game.ray.side == 0)
	{
		data->game.ray.wall_x = data->game.ray.pos_y
			+ data->game.ray.perp_wall_dist * data->game.ray.ray_dir_y;
	}
	else
	{
		data->game.ray.wall_x = data->game.ray.pos_x
			+ data->game.ray.perp_wall_dist * data->game.ray.ray_dir_x;
	}
	data->game.ray.wall_x -= floor((data->game.ray.wall_x));
	data->game.ray.tex_x = (int)(data->game.ray.wall_x * (double)(64));
	if (data->game.ray.side == 0 && data->game.ray.ray_dir_x > 0)
		data->game.ray.tex_x = 64 - data->game.ray.tex_x - 1;
	if (data->game.ray.side == 1 && data->game.ray.ray_dir_y < 0)
		data->game.ray.tex_x = 64 - data->game.ray.tex_x - 1;
	data->game.ray.step = 1.0 * 64 / data->game.ray.line_height;
	data->game.ray.tex_pos = (data->game.ray.draw_start - 1080 / 2
			+ data->game.ray.line_height / 2) * data->game.ray.step;
	data->game.ray.y = data->game.ray.draw_start;
}

void	choose_wall_texture(t_data *data)
{
	data->game.ray.tex_y = (int)data->game.ray.tex_pos & (64 - 1);
	data->game.ray.tex_pos += data->game.ray.step;
	if (data->game.ray.side == 0)
	{
		if (data->game.ray.ray_dir_x > 0)
			data->game.color = get_color_from_pixel(&data->game.wall_ea,
					data->game.ray.tex_x, data->game.ray.tex_y);
		else
			data->game.color = get_color_from_pixel(&data->game.wall_we,
					data->game.ray.tex_x, data->game.ray.tex_y);
	}
	else if (data->game.ray.side == 1)
	{
		if (data->game.ray.ray_dir_y > 0)
			data->game.color = get_color_from_pixel(&data->game.wall_so,
					data->game.ray.tex_x, data->game.ray.tex_y);
		else
			data->game.color = get_color_from_pixel(&data->game.wall_no,
					data->game.ray.tex_x, data->game.ray.tex_y);
	}
}

void	draw_walls(t_data *data)
{
	calculate_wall_collision(data);
	while (data->game.ray.y < data->game.ray.draw_end)
	{
		choose_wall_texture(data);
		if (data->game.ray.side == 1)
			data->game.color = (data->game.color >> 1) & 8355711;
		my_mlx_pixel_put(data, data->game.ray.x, data->game.ray.y,
			darken_color(data->game.color, data->game.ray.line_height));
		data->game.ray.y++;
	}
}

void	raycasting2d(t_data *data)
{
	data->game.ray.x = 0;
	while (data->game.ray.x < 1920)
	{
		update_ray_data(data);
		while (data->game.ray.hit == 0)
		{
			increment_ray(data);
			if (data->map.good_map[data->game.ray.map_y]
				[data->game.ray.map_x] == '1')
				data->game.ray.hit = 1;
		}
		perp_wall_dist_and_line_height(data);
		draw_walls(data);
		data->game.ray.x++;
	}
}
