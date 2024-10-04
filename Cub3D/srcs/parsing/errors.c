/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:47:19 by clement           #+#    #+#             */
/*   Updated: 2023/12/20 13:28:55 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ft_error(t_data *data, char *str, char *line)
{
	printf("Error\n%s\n", str);
	if (data->read)
		free(data->read);
	if (line)
		free(line);
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	if (data->f)
		free(data->f);
	if (data->c)
		free(data->c);
	ft_free_map(data->map.map);
	ft_free_map(data->map.copy_map);
	close(data->fd1);
	exit(0);
}

void	handle_line_map(t_data *data, char *line)
{
	if (settings_full(data))
		ft_error(data, "Invalid: settings not full", line);
	if (data->empty_line == 1)
		ft_error(data, "Invalid: empty line in map", line);
	add_line_to_map(data, line);
	data->map.height++;
}
