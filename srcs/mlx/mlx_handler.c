/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:26:20 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/11 16:16:05 by avancoll         ###   ########.fr       */
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

void	init_mlx(t_mlx_data *data)
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

static void	init_floor_ceiling(t_mlx_data *data)
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
	dst = data->map->img_data[side] + (y * data->size_line + x * (data->bits_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	x_value(t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)SIZE_X - 1;
	ray->ray_dir_x = ray->dir_x + (ray->plane_x * ray->camera_x);
	ray->ray_dir_y = ray->dir_y + (ray->plane_y * ray->camera_x);
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	ray_dir_value(t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1 - ray->pos_y) * ray->delta_dist_y;
	}
}

void	ray_hit(t_mlx_data *data)
{
	while (data->ray->hit == 0)
	{
		if (data->ray->side_dist_x < data->ray->side_dist_y)
		{
			data->ray->side_dist_x += data->ray->delta_dist_x;
			data->ray->map_x += data->ray->step_x;
			data->ray->side = 0;
		}
		else
		{
			data->ray->side_dist_y += data->ray->delta_dist_y;
			data->ray->map_y += data->ray->step_y;
			data->ray->side = 1;
		}
		if (data->map->map[data->ray->map_y][data->ray->map_x] == '1')
			data->ray->hit = 1;
		}
		if (data->ray->side == 0)
			data->ray->perp_wall_dist = (data->ray->side_dist_x - data->ray->delta_dist_x);
		else
			data->ray->perp_wall_dist = (data->ray->side_dist_y - data->ray->delta_dist_y);
}

void	draw_texture(t_mlx_data *data, t_ray *ray, int x)
{
	int		y;
	unsigned int	color;
	
	ray->tex_x = (int)(ray->wall_x * (double)data->map->tex_width);
	if(ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = data->map->tex_width - ray->tex_x - 1;
	if(ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = data->map->tex_width - ray->tex_x - 1;
	ray->step = 1.0 * data->map->tex_height / ray->line_height;
	ray->tex_pos = (ray->draw_start - SIZE_Y / 2 + ray->line_height / 2) * ray->step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (data->map->tex_height - 1);
		ray->tex_pos += ray->step;
		color = get_tex_color(data, ray->tex_x, ray->tex_y);
		mlx_put_pixel(data, x, y++, color);
	}
}
int	raycaster(t_mlx_data *data, t_ray *ray)
{
	int				x;

	x = 0;
	while (x < SIZE_X)
	{
		x_value(ray, x);
		ray_dir_value(ray);
		ray_hit(data);
		ray->line_height = (int)(SIZE_Y / ray->perp_wall_dist);
		ray->draw_start = -ray->line_height / 2 + SIZE_Y / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + SIZE_Y / 2;
		if (ray->draw_end >= SIZE_Y)
			ray->draw_end = SIZE_Y - 1;
		if (ray->side == 0)
			ray->wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
		else
			ray->wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
		ray->wall_x -= floor((ray->wall_x));
		draw_texture(data, ray, x++);
	}
	return (0);
}

void	key_move_ws(t_mlx_data *data)
{
	if (data->key->mv_forward == 1)
	{
		if (data->map->map[(int)(data->ray->pos_y)][(int)(data->ray->pos_x + data->ray->dir_x * data->ray->movespeed)] != '1')
					data->ray->pos_x += data->ray->dir_x * data->ray->movespeed;
		if (data->map->map[(int)(data->ray->pos_y + data->ray->dir_y
				* data->ray->movespeed)][(int)(data->ray->pos_x)] != '1')
			data->ray->pos_y += data->ray->dir_y * data->ray->movespeed;
	}
	if (data->key->mv_backward == 1)
	{
		if (data->map->map[(int)(data->ray->pos_y)][(int)(data->ray->pos_x
				- data->ray->dir_x * data->ray->movespeed)] != '1')
			data->ray->pos_x -= data->ray->dir_x * data->ray->movespeed;
		if (data->map->map[(int)(data->ray->pos_y - data->ray->dir_y
				* data->ray->movespeed)][(int)(data->ray->pos_x)] != '1')
			data->ray->pos_y -= data->ray->dir_y * data->ray->movespeed;
	}
}

void	key_move_ad(t_mlx_data *data)
{
	if (data->key->mv_left == 1)
	{
		if (data->map->map[(int)(data->ray->pos_y)][(int)(data->ray->pos_x
				- data->ray->plane_x * data->ray->movespeed)] != '1')
			data->ray->pos_x -= data->ray->plane_x * data->ray->movespeed;
		if (data->map->map[(int)(data->ray->pos_y - data->ray->plane_y
				* data->ray->movespeed)][(int)(data->ray->pos_x)] != '1')
			data->ray->pos_y -= data->ray->plane_y * data->ray->movespeed;
	}
	if (data->key->mv_right == 1)
	{
		if (data->map->map[(int)(data->ray->pos_y)][(int)(data->ray->pos_x
				+ data->ray->plane_x * data->ray->movespeed)] != '1')
			data->ray->pos_x += data->ray->plane_x * data->ray->movespeed;
		if (data->map->map[(int)(data->ray->pos_y + data->ray->plane_y
				* data->ray->movespeed)][(int)(data->ray->pos_x)] != '1')
			data->ray->pos_y += data->ray->plane_y * data->ray->movespeed;
	}
}

void	key_move_left(t_mlx_data *data)
{
	if (data->key->rot_left == 1)
	{
		double oldDirX = data->ray->dir_x;
		data->ray->dir_x = data->ray->dir_x * cos(data->ray->rotspeed)
			- data->ray->dir_y * sin(data->ray->rotspeed);
		data->ray->dir_y = oldDirX * sin(data->ray->rotspeed) + data->ray->dir_y
			* cos(data->ray->rotspeed);
		double oldPlaneX = data->ray->plane_x;
		data->ray->plane_x = data->ray->plane_x * cos(data->ray->rotspeed)
			- data->ray->plane_y * sin(data->ray->rotspeed);
		data->ray->plane_y = oldPlaneX * sin(data->ray->rotspeed)
			+ data->ray->plane_y * cos(data->ray->rotspeed);
	}
}

void	key_move_right(t_mlx_data *data)
{
	if (data->key->rot_right == 1)
	{
		double oldDirX = data->ray->dir_x;
		data->ray->dir_x = data->ray->dir_x * cos(-data->ray->rotspeed)
			- data->ray->dir_y * sin(-data->ray->rotspeed);
		data->ray->dir_y = oldDirX * sin(-data->ray->rotspeed)
			+ data->ray->dir_y * cos(-data->ray->rotspeed);
		double oldPlaneX = data->ray->plane_x;
		data->ray->plane_x = data->ray->plane_x * cos(-data->ray->rotspeed)
			- data->ray->plane_y * sin(-data->ray->rotspeed);
		data->ray->plane_y = oldPlaneX * sin(-data->ray->rotspeed)
			+ data->ray->plane_y * cos(-data->ray->rotspeed);
	}
}

int	exec_move(t_mlx_data *data)
{
	key_move_ws(data);
	key_move_ad(data);
	key_move_left(data);
	key_move_right(data);
	init_floor_ceiling(data);
	raycaster(data, data->ray);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}
