/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:56:18 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/11 14:29:15 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_close(t_mlx_data *data)
{
	if (data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}

int	filename_checker(char *str)
{
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
	return (0);
}

int	open_map(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("cub3D");
		return (1);
	}
	return (fd);
}

int	init_key(t_mlx_data *data)
{
	data->key = malloc(sizeof(t_key));
	if (!data->key)
		return (1);
	data->key->mv_forward = 0;
	data->key->mv_backward = 0;
	data->key->mv_left = 0;
	data->key->mv_right = 0;
	data->key->rot_left = 0;
	data->key->rot_right = 0;
	return (0);
}

int	free_all(t_mlx_data *data)
{
	if (data->map)
		ft_t_map_free(data->map);
	if (data->key)
		free(data->key);
	return (1);
}

int	main(int argc, char **argv)
{
	t_mlx_data	data;

	if (argc != 2 || filename_checker(argv[1]))
		return (1);
	data.map = map_init();
	parser(open_map(argv[1], &(data).map));
	if (!data.map)
		return (free_all(&data));
	init_mlx(&data);
	if (init_player(&data))
		return (free_all(&data));
	if (init_key(&data))
		return (free_all(&data));
	mlx_hook(data.win_ptr, ON_DESTROY, 0, ft_close, &data);
	mlx_hook(data.win_ptr, ON_KEYUP, 0, key_released, &data);
	mlx_hook(data.win_ptr, ON_KEYDOWN, 0, key_pressed, &data);
	mlx_loop_hook(data.mlx_ptr, exec_move, &data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_loop(data.mlx_ptr);
	return (0);
}
