/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:18:36 by clement           #+#    #+#             */
/*   Updated: 2023/12/13 17:36:36 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int	ft_close(void *da)
{
	t_data	*data;

	data = (t_data *) da;
	ft_end(data);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	data;	

	data.save = 0;
	ft_bzero(&data, sizeof(t_data));
	if (argc == 2 || (argc == 3 && ft_check_save(argv[2])))
	{
		if (argc == 3)
			data.save = 1;
		ft_cub(argv[1], &data);
	}
	else
	{
		printf("Error\n Wrong number of arguments.\n");
		exit(1);
	}
	display3d(&data);
	return (0);
}
