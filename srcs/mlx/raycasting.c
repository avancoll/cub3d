/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:11:59 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/11 17:31:15 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
		data->ray->perp_wall_dist = (data->ray->side_dist_x
				- data->ray->delta_dist_x);
	else
		data->ray->perp_wall_dist = (data->ray->side_dist_y
				- data->ray->delta_dist_y);
}

void	draw_texture(t_mlx_data *data, t_ray *ray, int x)
{
	int				y;
	unsigned int	color;

	ray->tex_x = (int)(ray->wall_x * (double)data->map->tex_width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = data->map->tex_width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = data->map->tex_width - ray->tex_x - 1;
	ray->step = 1.0 * data->map->tex_height / ray->line_height;
	ray->tex_pos = (ray->draw_start - SIZE_Y / 2 + ray->line_height / 2)
		* ray->step;
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
