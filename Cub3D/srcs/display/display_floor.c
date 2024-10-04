/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:36:02 by clement           #+#    #+#             */
/*   Updated: 2023/12/19 09:28:27 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	ft_display_floor(t_data *data, char *str)
{
	data->f = ft_strdup(str);
	if (ft_check_rgb(&data->floor, str) == -1)
		return (-1);
	return (0);
}

int	check_value(int nb, char *rgb)
{
	if (nb < 0 || nb > 255)
	{
		printf("Error\nRGB value must be between 0 and 255\n");
		free(rgb);
		return (-1);
	}
	return (0);
}

int	ft_get_rgb_value(char *str, t_floor *floor, int i)
{
	int		j;
	char	*rgb;
	int		size_rgb;
	int		nb;

	rgb = NULL;
	size_rgb = 0;
	while (ft_isdigit(str[i++]) == 1)
		size_rgb++;
	rgb = ft_calloc(sizeof(char), size_rgb + 1);
	if (rgb == NULL)
		return (-1);
	j = 0;
	i -= (size_rgb + 1);
	while (ft_isdigit(str[i]))
		rgb[j++] = str[i++];
	nb = ft_atoi(rgb);
	if (check_value(nb, rgb) == -1)
		return (-1);
	free(rgb);
	floor->index = i;
	return (nb);
}

int	ft_good_rgb_format(char *str, t_floor *floor)
{
	int	i;

	i = floor->index;
	if (str[i] == ',' && ft_isdigit(str[i + 1]) == 1)
	{
		i++;
		floor->index = i;
	}
	else
		return (-1);
	return (0);
}

int	ft_check_rgb(t_floor *floor, char *str)
{
	int	i;

	i = 0;
	ft_bzero(floor, sizeof(t_floor));
	while (ft_isdigit(str[i]) == 0)
	{
		if (str[i] == ',')
			return (printf("Error\nnot rgb's good format\n"), -1);
		i++;
	}
	floor->r_value = ft_get_rgb_value(str, floor, i);
	i = floor->index;
	if (ft_good_rgb_format(str, floor) == -1)
		return (printf("Error\nnot rgb's good format\n"), -1);
	floor->g_value = ft_get_rgb_value(str, floor, floor->index);
	i = floor->index;
	if (ft_good_rgb_format(str, floor) == -1)
		return (printf("Error\nnot rgb's good format\n"), -1);
	floor->b_value = ft_get_rgb_value(str, floor, floor->index);
	i = floor->index;
	if (str[i] != '\0')
		return (printf("Error\nformat is not good\n"), -1);
	return (0);
}
