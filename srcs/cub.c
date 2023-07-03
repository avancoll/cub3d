/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:56:18 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/03 18:43:02 by jusilanc         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_mlx_data data;

	(void)argc;
	(void)argv;
	mlx_handler(&data);
	mlx_hook(data.win_ptr, ON_DESTROY, 0, ft_close, &data);
	// mlx_hook(data.win_ptr, ON_KEYUP, 0, key_released, &data);
	// mlx_hook(data.win_ptr, ON_KEYDOWN, 0, key_pressed, &data);
	// mlx_loop_hook(data.mlx_ptr, exec_move, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}