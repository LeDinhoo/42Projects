/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:15:11 by clement           #+#    #+#             */
/*   Updated: 2023/12/19 17:21:38 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	ft_check_save(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == 'e' && str[i - 2] == 'v' && str[i - 3] == 'a' && str[i
			- 4] == 's' && str[i - 5] == '-' && str[i - 6] == '-'
		&& ft_strlen(str) < 7)
		return (1);
	else
		return (0);
}

int	ft_count_line(int fd)
{
	char	*line;
	char	*prev_line;
	int		nb;

	line = get_next_line(fd);
	if (!line)
		return (write(2, "Error\nMap is empty\n", 20));
	prev_line = NULL;
	nb = 0;
	while (line)
	{
		if (prev_line)
			free(prev_line);
		if (line[0])
			nb++;
		prev_line = line;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	if (ft_strlen(prev_line) == 0
		|| prev_line[ft_strlen(prev_line) - 1] == '\n')
		return (close(fd), free(prev_line), 0);
	return (close(fd), free(prev_line), nb);
}

int	ft_same_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i])
		return (1);
	return (0);
}

void	switch_space(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j])
	{
		while (map[j][i])
		{
			if (map[j][i] == ' ' || map[j][i] == '\t')
				map[j][i] = '1';
			i++;
		}
		i = 0;
		j++;
	}
}

int	check_border(t_map *map)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	(void)*map;
	if (ft_check_border_up(map, x) == -1)
		return (-1);
	x = map->width - 1;
	if (ft_check_border_right(map, y) == -1)
		return (-1);
	x = map->width - 1;
	if (ft_check_border_down(map, x) == -1)
		return (-1);
	y = map->height - 1;
	if (ft_check_border_left(map, y) == -1)
		return (-1);
	return (0);
}
