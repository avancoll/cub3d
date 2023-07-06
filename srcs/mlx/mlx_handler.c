/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:26:20 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/06 13:49:47 by avancoll         ###   ########.fr       */
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
void	init_player(t_ray *ray)
{
	ray = malloc(sizeof(t_ray));
	ray->pos_x = 22;
	ray->pos_y = 12;
	ray->dir_x = -1;
	ray->dir_y = 0;
	ray->plane_x = 0;
	ray->plane_y = 0.66;
	
}

int	raytracer(t_mlx_data *data, t_ray *ray)
{
	int	x;

	x = -1;
	while (++x < SIZE_X)
	{
		ray->camera_x = 2 * x / (double)SIZE_X - 1;
		ray->ray_dir_x = ray->ray_dir_x + ray->plane_x * ray->camera_x;
		ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
		ray->map_x = (int)ray->pos_x;
		ray->map_y = (int)ray->pos_y;
		
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);

		ray->hit = 0;
		if (ray->ray_dir_x < 0)
		{
			ray->step_x = -1;
			ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
		}
		else
		{
			ray->step_x = 1;
			ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
		}
		if (ray->ray_dir_y < 0)
		{
			ray->step_y = -1;
			ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
		}
		else
		{
			ray->step_y = 1;
			ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
		}
		while (ray->hit == 0)
		{
			if (ray->side_dist_x < ray->side_dist_y)
			{
				ray->side_dist_x += ray->delta_dist_x;
				ray->map_x += ray->step_x;
				ray->side = 0;
			}
			else
			{
				ray->side_dist_y += ray->delta_dist_y;
				ray->map_y += ray->step_y;
				ray->side = 1;
			}
			printf("x = %d, y = %d\n", ray->map_x, ray->map_y);
			// if (data->map->map[ray->map_x][ray->map_y] == '1')
				ray->hit = 1;
		}
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
		else
			ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
		ray->line_height = (int)(SIZE_Y / ray->perp_wall_dist);
		ray->draw_start = - ray->line_height / 2 + SIZE_Y / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + SIZE_Y / 2;
		if (ray->draw_end >= SIZE_Y)
			ray->draw_end = SIZE_Y - 1;
		int color;
		if (ray->side == 1)
			color = 0xFF0000;
		else
			color = 0x00FF00;
		printf("coucou\n");
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, ray->draw_start, color);
	}
	return (0);
}

int	exec_move(t_mlx_data *data)
{
	if (data->key->mv_forward == 1)
		write(1, "ford\n", 5);
	if (data->key->mv_backward == 1)
		write(1, "ford\n", 5);
	if (data->key->mv_left == 1)
		write(1, "ford\n", 5);
	if (data->key->mv_right == 1)
		write(1, "ford\n", 5);
	raytracer(data, data->ray);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}
