/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:25:07 by hdupuy            #+#    #+#             */
/*   Updated: 2023/11/30 10:25:38 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	set_ray_dir_x(t_data *data)
{
	if (data->game.ray.ray_dir_x < 0)
	{
		data->game.ray.step_x = -1;
		data->game.ray.side_dist_x = (data->game.ray.pos_x
				- data->game.ray.map_x) * data->game.ray.delta_dist_x;
	}
	else
	{
		data->game.ray.step_x = 1;
		data->game.ray.side_dist_x = (data->game.ray.map_x + 1.0
				- data->game.ray.pos_x) * data->game.ray.delta_dist_x;
	}
}

void	set_ray_dir_y(t_data *data)
{
	if (data->game.ray.ray_dir_y < 0)
	{
		data->game.ray.step_y = -1;
		data->game.ray.side_dist_y = (data->game.ray.pos_y
				- data->game.ray.map_y) * data->game.ray.delta_dist_y;
	}
	else
	{
		data->game.ray.step_y = 1;
		data->game.ray.side_dist_y = (data->game.ray.map_y + 1.0
				- data->game.ray.pos_y) * data->game.ray.delta_dist_y;
	}
}

void	update_ray_data(t_data *data)
{
	data->game.ray.camera_x = 2 * data->game.ray.x / (double)1920 - 1;
	data->game.ray.ray_dir_x = data->game.ray.dir_x + data->game.ray.plan_x
		* data->game.ray.camera_x;
	data->game.ray.ray_dir_y = data->game.ray.dir_y + data->game.ray.plan_y
		* data->game.ray.camera_x;
	data->game.ray.map_x = (int)data->game.ray.pos_x;
	data->game.ray.map_y = (int)data->game.ray.pos_y;
	data->game.ray.delta_dist_x = fabs(1 / data->game.ray.ray_dir_x);
	data->game.ray.delta_dist_y = fabs(1 / data->game.ray.ray_dir_y);
	data->game.ray.hit = 0;
	set_ray_dir_x(data);
	set_ray_dir_y(data);
}

void	increment_ray(t_data *data)
{
	if (data->game.ray.side_dist_x < data->game.ray.side_dist_y)
	{
		data->game.ray.side_dist_x += data->game.ray.delta_dist_x;
		data->game.ray.map_x += data->game.ray.step_x;
		data->game.ray.side = 0;
	}
	else
	{
		data->game.ray.side_dist_y += data->game.ray.delta_dist_y;
		data->game.ray.map_y += data->game.ray.step_y;
		data->game.ray.side = 1;
	}
}
