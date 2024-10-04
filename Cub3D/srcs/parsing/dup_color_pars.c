/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:56:08 by hdupuy            #+#    #+#             */
/*   Updated: 2023/12/19 09:56:54 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	dup_line2(t_data *data, char *line, int id)
{
	if (id == EA)
	{
		if (data->ea)
			ft_error(data, "Invalid: EA texture already set", line);
		line += 3;
		while (*line == ' ')
			line++;
		data->ea = ft_strdup(line);
	}
	else if (id == WE)
	{
		if (data->we)
			ft_error(data, "Invalid: WE texture already set", line);
		line += 3;
		while (*line == ' ')
			line++;
		data->we = ft_strdup(line);
	}
}

void	set_floor_rgb(t_data *data, char *line)
{
	char	**tab;

	tab = ft_split(line + 2, ',');
	data->floor.r_value = ft_atoi(tab[0]);
	data->floor.g_value = ft_atoi(tab[1]);
	data->floor.b_value = ft_atoi(tab[2]);
	ft_free_tab(tab);
}

void	set_ceiling_rgb(t_data *data, char *line)
{
	char	**tab;

	tab = ft_split(line + 2, ',');
	data->ceiling.r_value = ft_atoi(tab[0]);
	data->ceiling.g_value = ft_atoi(tab[1]);
	data->ceiling.b_value = ft_atoi(tab[2]);
	ft_free_tab(tab);
}

void	dup_color(t_data *data, char *line, int id)
{
	if (id == F)
	{
		if (data->f)
			ft_error(data, "Invalid: F color already set", line);
		data->f = ft_strdup(line);
		set_floor_rgb(data, line);
	}
	else if (id == C)
	{
		if (data->c)
			ft_error(data, "Invalid: C color already set", line);
		data->c = ft_strdup(line);
		set_ceiling_rgb(data, line);
	}
}

void	dup_line(t_data *data, char *line, int id)
{
	if (!line)
		ft_error(data, "Invalid texture name", line);
	if (id == NO)
	{
		if (data->no)
			ft_error(data, "Invalid: NO texture already set", line);
		line += 3;
		while (*line == ' ')
			line++;
		data->no = ft_strdup(line);
	}
	else if (id == SO)
	{
		if (data->so)
			ft_error(data, "Invalid: SO texture already set", line);
		line += 3;
		while (*line == ' ')
			line++;
		data->so = ft_strdup(line);
	}
	dup_line2(data, line, id);
}
