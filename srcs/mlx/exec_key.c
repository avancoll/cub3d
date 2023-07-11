/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:13:02 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/11 17:29:46 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	key_move_ws(t_mlx_data *data)
{
	if (data->key->mv_forward == 1)
	{
		if (data->map->map[(int)(data->ray->pos_y)][(int)(data->ray->pos_x
			+ data->ray->dir_x * data->ray->movespeed)] != '1')
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
	double	old_dir_x;
	double	old_plane_x;

	if (data->key->rot_left == 1)
	{
		old_dir_x = data->ray->dir_x;
		data->ray->dir_x = data->ray->dir_x * cos(data->ray->rotspeed)
			- data->ray->dir_y * sin(data->ray->rotspeed);
		data->ray->dir_y = old_dir_x * sin(data->ray->rotspeed)
			+ data->ray->dir_y * cos(data->ray->rotspeed);
		old_plane_x = data->ray->plane_x;
		data->ray->plane_x = data->ray->plane_x * cos(data->ray->rotspeed)
			- data->ray->plane_y * sin(data->ray->rotspeed);
		data->ray->plane_y = old_plane_x * sin(data->ray->rotspeed)
			+ data->ray->plane_y * cos(data->ray->rotspeed);
	}
}

void	key_move_right(t_mlx_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	if (data->key->rot_right == 1)
	{
		old_dir_x = data->ray->dir_x;
		data->ray->dir_x = data->ray->dir_x * cos(-data->ray->rotspeed)
			- data->ray->dir_y * sin(-data->ray->rotspeed);
		data->ray->dir_y = old_dir_x * sin(-data->ray->rotspeed)
			+ data->ray->dir_y * cos(-data->ray->rotspeed);
		old_plane_x = data->ray->plane_x;
		data->ray->plane_x = data->ray->plane_x * cos(-data->ray->rotspeed)
			- data->ray->plane_y * sin(-data->ray->rotspeed);
		data->ray->plane_y = old_plane_x * sin(-data->ray->rotspeed)
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
