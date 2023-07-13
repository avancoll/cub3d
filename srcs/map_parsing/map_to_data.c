/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:59:46 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/13 14:31:18 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	get_player_dir_ns(t_mlx_data *data)
{
	if (data->map->map
		&& data->map->map[(int)data->ray->pos_y][(int)data->ray->pos_x]
		== 'N')
	{
		data->ray->dir_x = 0;
		data->ray->dir_y = -1;
		data->ray->plane_x = -0.66;
		data->ray->plane_y = 0;
	}
	else if (data->map->map
		&& data->map->map[(int)data->ray->pos_y][(int)data->ray->pos_x]
		== 'S')
	{
		data->ray->dir_x = 0;
		data->ray->dir_y = 1;
		data->ray->plane_x = 0.66;
		data->ray->plane_y = 0;
	}
}

static void	get_player_dir_we(t_mlx_data *data)
{
	if (data->map->map
		&& data->map->map[(int)data->ray->pos_y][(int)data->ray->pos_x]
		== 'E')
	{
		data->ray->dir_x = -1;
		data->ray->dir_y = 0;
		data->ray->plane_x = 0;
		data->ray->plane_y = 0.66;
	}
	else if (data->map->map
		&& data->map->map[(int)data->ray->pos_y][(int)data->ray->pos_x]
		== 'W')
	{
		data->ray->dir_x = 1;
		data->ray->dir_y = 0;
		data->ray->plane_x = 0;
		data->ray->plane_y = -0.66;
	}
}

static void	get_player_pos(t_mlx_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (data->map->map && data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (ft_strchr("NSWE", data->map->map[y][x]))
			{
				data->ray->pos_x = x + 0.5;
				data->ray->pos_y = y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	init_player(t_mlx_data *data)
{
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		return (1);
	data->ray->movespeed = 0.0553;
	data->ray->rotspeed = 0.0553;
	get_player_pos(data);
	get_player_dir_ns(data);
	get_player_dir_we(data);
	get_texture_addr(data);
	if (!data->map->img_data)
		return (1);
	return (0);
}
