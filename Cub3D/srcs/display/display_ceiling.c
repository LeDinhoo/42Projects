/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_ceiling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:36:10 by clement           #+#    #+#             */
/*   Updated: 2023/12/15 15:35:33 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	ft_display_ceiling(t_data *data, char *str)
{
	data->c = ft_strdup(str);
	if (ft_check_rgb_ce(&data->ceiling, str) == -1)
		return (-1);
	return (0);
}

int	ft_get_rgb_value_ce(char *str, t_ceiling *ceiling, int i)
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
	if (nb < 0 || nb > 255)
	{
		printf("Error\nRGB's value must be between 0 & 255\n");
		free(rgb);
		return (-1);
	}
	ceiling->index = i;
	return (free(rgb), nb);
}

int	ft_good_rgb_format_ce(char *str, t_ceiling *ceiling)
{
	int	i;

	i = ceiling->index;
	if (str[i] == ',' && ft_isdigit(str[i + 1]) == 1)
	{
		i++;
		ceiling->index = i;
	}
	else
		return (-1);
	return (0);
}

int	ft_check_rgb_ce(t_ceiling *ceiling, char *str)
{
	int	i;

	i = 0;
	ft_bzero(ceiling, sizeof(t_ceiling));
	while (ft_isdigit(str[i]) == 0)
	{
		if (str[i] == ',')
			return (printf("Error\nnot rgb's good format\n"), -1);
		i++;
	}
	ceiling->r_value = ft_get_rgb_value_ce(str, ceiling, i);
	printf("r = %d\n", ceiling->r_value);
	i = ceiling->index;
	if (ft_good_rgb_format_ce(str, ceiling) == -1)
		return (printf("Error\nnot rgb's good format for ceiling1\n"), -1);
	ceiling->g_value = ft_get_rgb_value_ce(str, ceiling, ceiling->index);
	i = ceiling->index;
	if (ft_good_rgb_format_ce(str, ceiling) == -1)
		return (printf("Error\nnot rgb's good format for ceiling2\n"), -1);
	ceiling->b_value = ft_get_rgb_value_ce(str, ceiling, ceiling->index);
	i = ceiling->index;
	if (str[i] != '\0')
		return (printf("Error\nformat is not good\n"), -1);
	return (0);
}
