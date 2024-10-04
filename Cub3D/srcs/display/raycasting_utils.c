/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:40:38 by hdupuy            #+#    #+#             */
/*   Updated: 2023/12/18 11:09:09 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_window	ft_new_window(void *mlx, int widht, int height, char *name)
{
	t_window	window;

	window.ref = mlx_new_window(mlx, widht, height, name);
	window.size.x = widht;
	window.size.y = height;
	return (window);
}

void	set_direction(t_ray *ray, const t_direction_params *params)
{
	ray->dir_x = params->dir_x;
	ray->dir_y = params->dir_y;
	ray->plan_x = params->plan_x;
	ray->plan_y = params->plan_y;
}

void	set_player_orientation(t_data *data, char orientation)
{
	t_direction_params	params;

	if (orientation == 'W')
		params = (t_direction_params){-1, 0, 0, -0.66};
	else if (orientation == 'E')
		params = (t_direction_params){1, 0, 0, 0.66};
	else if (orientation == 'N')
		params = (t_direction_params){0, -1, 0.66, 0};
	else if (orientation == 'S')
		params = (t_direction_params){0, 1, -0.66, 0};
	set_direction(&(data->game.ray), &params);
}

void	find_start_pos(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map.good_map[i])
	{
		j = 0;
		while (data->map.good_map[i][j])
		{
			if (data->map.good_map[i][j] == 'N'
				|| data->map.good_map[i][j] == 'S'
				|| data->map.good_map[i][j] == 'W'
				|| data->map.good_map[i][j] == 'E')
			{
				data->player.px = j;
				data->player.py = i;
				set_player_orientation(data, data->map.good_map[i][j]);
			}
			j++;
		}
		i++;
	}
}

void	double_buffering(t_data *data)
{
	if (data->game.is_buffer == 1)
	{
		mlx_put_image_to_window(data->game.mlx, data->game.win.ref,
			data->game.buffer2.img, 0, 0);
		data->game.is_buffer = 2;
	}
	else
	{
		mlx_put_image_to_window(data->game.mlx, data->game.win.ref,
			data->game.buffer1.img, 0, 0);
		data->game.is_buffer = 1;
	}
}
