/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:38:22 by hdupuy            #+#    #+#             */
/*   Updated: 2023/12/19 09:28:05 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	create_rgb(int r, int g, int b)
{
	int	color;

	color = r;
	color = (color << 8) + g;
	color = (color << 8) + b;
	return (color);
}

void	init_game(t_data *data)
{
	data->game.mlx = mlx_init();
	if (!data->game.mlx)
		return ;
	data->game.win = ft_new_window(data->game.mlx, 1920, 1080, "Cub3D");
	data->game.square_size = 16;
	data->game.player_size = 8;
	data->game.ray.dir_x = -1;
	data->game.ray.dir_y = 0;
	data->game.mapx = data->map.width;
	data->game.mapy = data->map.height;
	data->game.maps = data->game.square_size;
	data->game.angle = 0;
	data->game.is_buffer = 0;
	find_start_pos(data);
	data->game.ray.pos_x = data->player.px + 0.5;
	data->game.ray.pos_y = data->player.py + 0.5;
	data->game.ceiling_color = create_rgb(data->ceiling.r_value,
			data->ceiling.g_value, data->ceiling.b_value);
	data->game.floor_color = create_rgb(data->floor.r_value,
			data->floor.g_value, data->floor.b_value);
}

t_img	ft_new_sprite(void *mlx, char *path, t_data *prog)
{
	t_image_node	*node;

	node = malloc(sizeof(t_image_node));
	if (node == NULL)
		free(node);
	node->image.img = mlx_xpm_file_to_image(mlx, path, &node->image.height,
			&node->image.width);
	if (node->image.img == NULL)
	{
		printf("Error\nUnable to create the XPM file.%s\n", path);
		free(node);
		ft_end(prog);
	}
	node->image.addr = mlx_get_data_addr(node->image.img,
			&node->image.bits_per_pixel, &node->image.line_length,
			&node->image.endian);
	node->next = prog->g_image_list;
	prog->g_image_list = node;
	return (node->image);
}

void	create_buffer_and_image(t_data *data)
{
	data->game.buffer1.img = mlx_new_image(data->game.mlx, 1920, 1080);
	data->game.buffer1.addr = mlx_get_data_addr(data->game.buffer1.img,
			&data->game.buffer1.bits_per_pixel, &data->game.buffer1.line_length,
			&data->game.buffer1.endian);
	data->game.buffer2.img = mlx_new_image(data->game.mlx, 1920, 1080);
	data->game.buffer2.addr = mlx_get_data_addr(data->game.buffer2.img,
			&data->game.buffer2.bits_per_pixel, &data->game.buffer2.line_length,
			&data->game.buffer2.endian);
	data->game.wall_no = ft_new_sprite(data->game.mlx, data->no, data);
	data->game.wall_so = ft_new_sprite(data->game.mlx, data->so, data);
	data->game.wall_ea = ft_new_sprite(data->game.mlx, data->ea, data);
	data->game.wall_we = ft_new_sprite(data->game.mlx, data->we, data);
}

int	display3d(t_data *data)
{
	init_game(data);
	create_buffer_and_image(data);
	mlx_hook(data->game.win.ref, 2, 1L << 0, *key_press, data);
	mlx_hook(data->game.win.ref, 17, 0, ft_close, data);
	mlx_hook(data->game.win.ref, 3, 1L << 1, *key_release, data);
	mlx_loop_hook(data->game.mlx, move_and_redraw, data);
	mlx_loop(data->game.mlx);
	return (0);
}
