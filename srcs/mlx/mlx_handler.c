/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:26:20 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/03 18:47:08 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	mlx_put_pixel(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < SIZE_X && y < SIZE_Y)
	{
		dst = data->addr + (y * data->size_line + x * (data->bits_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	mlx_handler(t_mlx_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, SIZE_X, SIZE_Y, "cub3D");
	data->img_ptr = mlx_new_image(data->mlx_ptr, SIZE_X, SIZE_Y);
	data->addr = mlx_get_data_addr(data->img_ptr, &data->bits_pixel,
			&data->size_line, &data->endian);
}

int	key_pressed(int keycode, t_mlx_data *data)
{
	if (keycode == KEY_ESC)
		ft_close(data);
	if (keycode == KEY_W)
		data->key->mv_forward = 1;
	if (keycode == KEY_S)
		data->key->mv_backward = 1;
	if (keycode == KEY_A)
		data->key->mv_left = 1;
	if (keycode == KEY_D)
		data->key->mv_right = 1;
	return (0);
}

int	key_released(int keycode, t_mlx_data *data)
{
	if (keycode == KEY_W)
		data->key->mv_forward = 0;
	if (keycode == KEY_S)
		data->key->mv_backward = 0;
	if (keycode == KEY_A)
		data->key->mv_left = 0;
	if (keycode == KEY_D)
		data->key->mv_right = 0;
	return (0);
}

int	exec_move(t_mlx_data *data)
{
	if (data->key->mv_forward == 1)
		;
	if (data->key->mv_backward == 1)
		;
	if (data->key->mv_left == 1)
		;
	if (data->key->mv_right == 1)
		;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}
