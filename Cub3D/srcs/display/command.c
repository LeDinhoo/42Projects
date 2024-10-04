/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:46:56 by hdupuy            #+#    #+#             */
/*   Updated: 2023/12/18 13:39:27 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_free_images(t_data *data)
{
	t_image_node	*node;
	t_image_node	*temp;

	node = data->g_image_list;
	while (node != NULL)
	{
		mlx_destroy_image(data->game.mlx, node->image.img);
		temp = node;
		node = node->next;
		free(temp);
	}
	data->g_image_list = NULL;
}

int	ft_end(t_data *data)
{
	ft_free_map(data->map.copy_map);
	ft_free_map(data->map.map);
	ft_free_images(data);
	mlx_destroy_image(data->game.mlx, data->game.buffer1.img);
	mlx_destroy_image(data->game.mlx, data->game.buffer2.img);
	mlx_destroy_window(data->game.mlx, data->game.win.ref);
	mlx_destroy_display(data->game.mlx);
	free(data->no);
	free(data->so);
	free(data->ea);
	free(data->we);
	free(data->f);
	free(data->c);
	free(data->game.mlx);
	data->game.mlx = NULL;
	exit(0);
}

int	key_press(int key, void *da)
{
	t_data	*data;

	data = (t_data *)da;
	if (key == 65307)
		ft_end(data);
	if (key == 'w' || key == 65362)
		data->game.w = 1;
	if (key == 's' || key == 65364)
		data->game.s = 1;
	if (key == 'd' || key == 65363)
		data->game.d = 1;
	if (key == 'a' || key == 65361)
		data->game.a = 1;
	return (0);
}

int	key_release(int key, void *da)
{
	t_data	*data;

	data = (t_data *)da;
	if (key == 'w' || key == 65362)
		data->game.w = 0;
	if (key == 's' || key == 65364)
		data->game.s = 0;
	if (key == 'd' || key == 65363)
		data->game.d = 0;
	if (key == 'a' || key == 65361)
		data->game.a = 0;
	return (0);
}
