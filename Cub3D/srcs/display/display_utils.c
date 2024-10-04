/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:09:34 by hdupuy            #+#    #+#             */
/*   Updated: 2023/11/30 08:21:49 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

long long int	init_fps(void)
{
	struct timeval	tstart;

	gettimeofday(&tstart, NULL);
	return (tstart.tv_sec * 1000LL + tstart.tv_usec / 1000);
}

int	calculate_steps(int dx, int dy)
{
	if (abs(dx) > abs(dy))
		return (abs(dx));
	else
		return (abs(dy));
}

int	get_color_from_pixel(t_img *img, int x, int y)
{
	char	*dst;
	int		color;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (data->game.is_buffer == 1)
		dst = data->game.buffer2.addr + (y * data->game.buffer2.line_length + x
				* (data->game.buffer2.bits_per_pixel / 8));
	else
		dst = data->game.buffer1.addr + (y * data->game.buffer1.line_length + x
				* (data->game.buffer1.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	darken_color(int color, float factor)
{
	int	red;
	int	green;
	int	blue;

	if (factor > 720)
		factor = 720;
	factor = (factor / 360);
	if (factor > 1)
		factor = 1;
	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	red *= factor;
	green *= factor;
	blue *= factor;
	return ((red << 16) | (green << 8) | blue);
}
