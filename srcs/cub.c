/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:56:18 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/11 17:23:55 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

int	main(int argc, char **argv)
{
	t_mlx_data	data;
	int			fd;
	int			ret;

	if (argc != 2 || filename_checker(argv[1]))
		return (1);
	if (map_init(&data))
		return (1);
	if (!data.map)
		return (1);
	fd = open_map(argv[1]);
	ret = parser(fd, data.map);
	if (ret)
		return (free_all(&data));
	close(fd);
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
