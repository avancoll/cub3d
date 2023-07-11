/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:26:20 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/11 17:25:57 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	mlx_put_pixel(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < SIZE_X && y < SIZE_Y)
	{
		dst = data->addr + (y * SIZE_X * 4 + x * (data->bits_pixel / 8));
		*(unsigned int *)dst = color;
	}
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
	if (keycode == KEY_LEFT)
		data->key->rot_left = 1;
	if (keycode == KEY_RIGHT)
		data->key->rot_right = 1;
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
	if (keycode == KEY_LEFT)
		data->key->rot_left = 0;
	if (keycode == KEY_RIGHT)
		data->key->rot_right = 0;
	return (0);
}

void	init_floor_ceiling(t_mlx_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < SIZE_Y / 2)
	{
		x = 0;
		while (x < SIZE_X)
			mlx_put_pixel(data, x++, y, data->map->ceiling);
		y++;
	}
	while (y < SIZE_Y)
	{
		x = 0;
		while (x < SIZE_X)
			mlx_put_pixel(data, x++, y, data->map->floor);
		y++;
	}
}

int	get_tex_color(t_mlx_data *data, int x, int y)
{
	int		color;
	char	*dst;
	int		side;

	if (data->ray->side == 1)
	{
		if (data->ray->ray_dir_y >= 0)
			side = 1;
		else
			side = 0;
	}
	else
	{
		if (data->ray->ray_dir_x >= 0)
			side = 2;
		else
			side = 3;
	}
	dst = data->map->img_data[side]
		+ (y * data->size_line + x * (data->bits_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}
