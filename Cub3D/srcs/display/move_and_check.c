/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:56:57 by hdupuy            #+#    #+#             */
/*   Updated: 2023/12/19 09:27:20 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	check_and_move_up(t_data *data)
{
	if (data->map.good_map[(int)(data->game.ray.pos_y + data->game.ray.dir_y
			* data->game.ray.move_speed)][(int)data->game.ray.pos_x] != '1')
		data->game.ray.pos_y += data->game.ray.dir_y
			* data->game.ray.move_speed;
	if (data->map.good_map[(int)data->game.ray.pos_y][(int)(data->game.ray.pos_x
		+ data->game.ray.dir_x * data->game.ray.move_speed)] != '1')
		data->game.ray.pos_x += data->game.ray.dir_x
			* data->game.ray.move_speed;
}

void	check_and_move_down(t_data *data)
{
	if (data->map.good_map[(int)(data->game.ray.pos_y - data->game.ray.dir_y
			* data->game.ray.move_speed)][(int)data->game.ray.pos_x] != '1')
		data->game.ray.pos_y -= data->game.ray.dir_y
			* data->game.ray.move_speed;
	if (data->map.good_map[(int)data->game.ray.pos_y][(int)(data->game.ray.pos_x
		- data->game.ray.dir_x * data->game.ray.move_speed)] != '1')
		data->game.ray.pos_x -= data->game.ray.dir_x
			* data->game.ray.move_speed;
}

void	check_and_rotate_right(t_data *data)
{
	data->game.ray.old_dir_x = data->game.ray.dir_x;
	data->game.ray.dir_x = data->game.ray.dir_x * cos(data->game.ray.rot_speed)
		- data->game.ray.dir_y * sin(data->game.ray.rot_speed);
	data->game.ray.dir_y = data->game.ray.old_dir_x
		* sin(data->game.ray.rot_speed) + data->game.ray.dir_y
		* cos(data->game.ray.rot_speed);
	data->game.ray.old_plane_x = data->game.ray.plan_x;
	data->game.ray.plan_x = data->game.ray.plan_x
		* cos(data->game.ray.rot_speed) - data->game.ray.plan_y
		* sin(data->game.ray.rot_speed);
	data->game.ray.plan_y = data->game.ray.old_plane_x
		* sin(data->game.ray.rot_speed) + data->game.ray.plan_y
		* cos(data->game.ray.rot_speed);
}

void	check_and_rotate_left(t_data *data)
{
	data->game.ray.old_dir_x = data->game.ray.dir_x;
	data->game.ray.dir_x = data->game.ray.dir_x * cos(-data->game.ray.rot_speed)
		- data->game.ray.dir_y * sin(-data->game.ray.rot_speed);
	data->game.ray.dir_y = data->game.ray.old_dir_x
		* sin(-data->game.ray.rot_speed) + data->game.ray.dir_y
		* cos(-data->game.ray.rot_speed);
	data->game.ray.old_plane_x = data->game.ray.plan_x;
	data->game.ray.plan_x = data->game.ray.plan_x
		* cos(-data->game.ray.rot_speed) - data->game.ray.plan_y
		* sin(-data->game.ray.rot_speed);
	data->game.ray.plan_y = data->game.ray.old_plane_x
		* sin(-data->game.ray.rot_speed) + data->game.ray.plan_y
		* cos(-data->game.ray.rot_speed);
}

int	move_and_redraw(void *d)
{
	t_data	*data;

	data = (t_data *)d;
	data->game.old_time = data->game.time;
	if (data->game.w != 0)
		check_and_move_up(data);
	if (data->game.s != 0)
		check_and_move_down(data);
	if (data->game.d != 0)
		check_and_rotate_right(data);
	if (data->game.a != 0)
		check_and_rotate_left(data);
	drawbackground(data, 0, 0);
	raycasting2d(data);
	draw_map(data);
	double_buffering(data);
	data->game.time = init_fps();
	data->game.frame_time = (data->game.time - data->game.old_time) / 1000.0;
	data->game.ray.move_speed = data->game.frame_time * 5.0;
	data->game.ray.rot_speed = data->game.frame_time * 3.0;
	return (0);
}
