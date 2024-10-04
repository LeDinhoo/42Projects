/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:12:43 by clement           #+#    #+#             */
/*   Updated: 2023/12/14 15:22:36 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

int	ft_check_elem(t_data *data, char *str)
{
	int	id;

	id = ft_get_ident(str, data);
	if (id == -1)
		return (printf("Error\nIdentifier not found\n"), -1);
	if (id == NO || id == SO || id == WE || id == EA)
	{
		if (ft_display_walls(id, data, str) == -1)
			return (-1);
	}
	else if (id == F)
	{
		if (data->f)
			return (printf("Error\ntoo many elements\n"), -1);
		if (ft_display_floor(data, str) == -1)
			return (-1);
	}
	else if (id == C)
	{
		if (data->c)
			return (printf("Error\ntoo many elements\n"), -1);
		if (ft_display_ceiling(data, str) == -1)
			return (-1);
	}
	return (0);
}

int	ft_no_dble(char *line, int fd, t_data *data)
{
	int	i;

	i = 0;
	while (ft_strlen(line) == 0)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			return (printf("Error\nthere is no map\n"),
				ft_free_ident(data), close(fd), exit(1), -1);
	}
	while (line && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] != '1')
		return (-1);
	free(line);
	line = get_next_line(fd);
	free(line);
	return (0);
}

char	*ft_skip_empy_line(char *line, int fd)
{
	free(line);
	line = get_next_line(fd);
	return (line);
}

int	ft_check_dble(t_data *data, char *line, int fd)
{
	free(line);
	line = get_next_line(fd);
	if (ft_no_dble(line, fd, data) == -1)
		return (printf("Error\nToo many elements\n"), ft_free_ident(data),
			free(line), close(fd), exit(1), -1);
	else
		return (0);
	return (0);
}

void	ft_set_textures(t_data *data, int fd)
{
	char	*line;
	int		nb_elem;

	line = get_next_line(fd);
	nb_elem = 0;
	while (line && (nb_elem < 6))
	{
		if (ft_strlen(line) == 0)
		{
			line = ft_skip_empy_line(line, fd);
			continue ;
		}
		if (ft_check_elem(data, line) == -1)
			return (ft_free_ident(data), free(line), close(fd), exit(1));
		nb_elem++;
		if (nb_elem == 6 && data->c && data->f && data->no && data->so
			&& data->we && data->ea && ft_check_dble(data, line, fd) == 0)
			return ;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (nb_elem != 6)
		return (printf("Error\nnot enough elements\n"), exit(1));
}

/*void	ft_set_textures(t_data *data, int fd)
{
	char	*line;
	int		nb_elem;

	line = get_next_line(fd);
	nb_elem = 0;
	while (line && (nb_elem < 6))
	{
		if (ft_strlen(line) == 0)
		{
			line = ft_skip_empy_line(line, fd);
			continue ;
		}
		if (ft_check_elem(data, line) == -1)
			return (ft_free_ident(data), free(line), close(fd), exit(1));
		nb_elem++;
		if (nb_elem == 6 && data->c && data->f
			&& data->no && data->so && data->we && data->ea)
		{	
			if (ft_check_dble(data, line, fd) == 0)
				return ;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (nb_elem != 6)
		return (printf("Error\nnot enough elements\n"), exit(1));
}*/

/*void	ft_set_textures(t_data *data, int fd)
{
	char	*line;
	int		nb_elem;

	line = get_next_line(fd);
	nb_elem = 0;
	while (line && (nb_elem < 6))
	{
		if (ft_strlen(line) == 0)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (ft_check_elem(data, line) == -1)
			return (ft_free_ident(data), free(line), close(fd), exit(1));
		nb_elem++;
		if (nb_elem == 6 && data->c && data->f
			&& data->no && data->so && data->we && data->ea)
		{	
			free(line);
			line = get_next_line(fd);
			printf("line fin des 6 elem : :%s\n", line);
			if (ft_no_dble(line, fd, data) == -1)
				return (printf("Error\nToo many elements\n"), ft_free_ident(data),
					free(line), close(fd), exit(1));
			else
				return ;
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (nb_elem != 6)
		return (printf("Error\nnot enough elements\n"), exit(1));
}*/
