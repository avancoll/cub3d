/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:56:18 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/11 18:00:47 by avancoll         ###   ########.fr       */
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
		return (-1);
	}
	return (fd);
}

int	main(int argc, char **argv)
{
	t_mlx_data	data;
	int			fd;
	int			ret;

	if (argc != 2)
		return (display_error(NULL, 1));
	if (filename_checker(argv[1]))
		return (display_error(NULL, 2));
	if (init_map(&data))
		return (display_error(NULL, 3));
	fd = open_map(argv[1]);
	if (fd == -1)
		return (display_error(&data, 4));
	ret = parser(fd, data.map, 0);
	if (ret)
		return (display_error(&data, ret));      //return (free_all(&data)); ici il faut close(fd) attention !
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
