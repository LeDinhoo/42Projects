/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_digitcheck.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:53:50 by hdupuy            #+#    #+#             */
/*   Updated: 2023/12/19 17:04:47 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	ft_check_extension(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
		i++;
	while (line[i] != '.')
	{
		i--;
		if (i == 0)
			return (-1);
	}
	if (line[i + 1] == 'x' && line[i + 2] == 'p' && line[i + 3] == 'm' && line[i
			+ 4] == '\0')
		return (0);
	else
		return (-1);
}

int	check_color(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		return (-1);
	return (0);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	valid_color(char *line)
{
	char	**tab;
	int		r;
	int		g;
	int		b;

	if (!line)
		return (-1);
	tab = ft_split(line + 2, ',');
	if (!tab[0] || !tab[1] || !tab[2] || is_digit(tab[0]) == -1
		|| is_digit(tab[1]) == -1 || is_digit(tab[2]) == -1)
	{
		ft_free_tab(tab);
		return (-1);
	}
	r = ft_atoi(tab[0]);
	g = ft_atoi(tab[1]);
	b = ft_atoi(tab[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ft_free_tab(tab), -1);
	ft_free_tab(tab);
	return (0);
}
