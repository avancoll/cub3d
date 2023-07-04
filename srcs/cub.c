/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:56:18 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/04 15:47:28 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_close(t_mlx_data *data)
{
	if (data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	//free_map();
	//free_data();
	exit(0);
}

int	open_map(char *str)
{
	int	fd;

	if (ft_strlen(str) > 4)
	{
		if (ft_strcmp(str + ft_strlen(str) - 4, ".cub"))
		{
			write(2, "Error: Wrong file extension\n", 29);
			return (1);
		}
	}
	else
		return (1);
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("cub3D");
		return (1);
	}
	return (0);
}


int	main(int argc, char **argv)
{
	t_mlx_data data;

	if (argc != 2 || open_map(argv[1]))
		return (1);
	mlx_handler(&data);
	mlx_hook(data.win_ptr, ON_DESTROY, 0, ft_close, &data);
	mlx_hook(data.win_ptr, ON_KEYUP, 0, key_released, &data);
	mlx_hook(data.win_ptr, ON_KEYDOWN, 0, key_pressed, &data);
	mlx_loop_hook(data.mlx_ptr, exec_move, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}