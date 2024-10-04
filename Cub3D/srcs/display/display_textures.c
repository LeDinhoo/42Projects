/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:57:07 by clement           #+#    #+#             */
/*   Updated: 2023/12/15 12:04:05 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	*ft_get_file_name(char *line)
{
	char	*name;
	int		i;

	i = 0;
	while (ft_isalpha(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	if (strlen(&line[i]) == 0)
		return (NULL);
	name = &line[i];
	return (name);
}

int	set_texture(char *file, char **dest, char *direction, t_data *data)
{
	(void) *direction;
	(void) *data;
	if (*dest)
	{
		printf("Error\ntoo much elements\n");
		return (-1);
	}
	*dest = ft_strdup(file);
	return (0);
}

int	ft_display_walls(int id, t_data *data, char *str)
{
	char	*file;

	file = ft_get_file_name(str);
	if (!file)
		return (printf("Error\nimg file is not good\n"), -1);
	if (id == NO)
		return (set_texture(file, &(data->no), "NO", data));
	else if (id == SO)
		return (set_texture(file, &(data->so), "SO", data));
	else if (id == EA)
		return (set_texture(file, &(data->ea), "EA", data));
	else if (id == WE)
		return (set_texture(file, &(data->we), "WE", data));
	return (0);
}

/*int	ft_display_walls(int id, t_data *data, char *str)
{
	char	*file;

	file = ft_get_file_name(str);
	if (!file)
		return (printf("Error\nimg file is not good\n"), -1);
	if (id == NO)
	{
		if (data->no)
			return (printf("Error\ntoo much elements\n"), -1);
		data->no = ft_strdup(file);
	}
	if (id == SO)
	{
		if (data->so)
			return (printf("Error\ntoo much elements\n"), -1);
		data->so = ft_strdup(file);
	}
	if (id == EA)
	{
		if (data->ea)
			return (printf("Error\ntoo much elements\n"), -1);
		data->ea = ft_strdup(file);
	}
	if (id == WE)
	{
		if (data->we)
			return (printf("Error\ntoo much elements\n"), -1);
		data->we = ft_strdup(file);
	}
	return (0);
}*/
