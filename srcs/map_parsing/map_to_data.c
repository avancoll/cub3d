/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:59:46 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/06 18:39:24 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	get_player_dir(double *dir_x, double *dir_y, t_vect *ppos,
		char **map)
{
	if (map[ppos->y][ppos->x] == 'N')
	{
		*dir_x = 0;
		*dir_y = 1;
	}
	else if (map[ppos->y][ppos->x] == 'S')
	{
		*dir_x = 0;
		*dir_y = -1;
	}
	else if (map[ppos->y][ppos->x] == 'W')
	{
		*dir_x = -1;
		*dir_y = 0;
	}
	else if (map[ppos->y][ppos->x] == 'E')
	{
		*dir_x = 1;
		*dir_y = 0;
	}
}

static t_vect	get_player_pos(char **map)
{
	t_vect	player_pos;
	int		x;
	int		y;

	player_pos.x = -1;
	player_pos.y = -1;
	y = 0;
	while (map && map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("NSWE", map[y][x]))
			{
				player_pos.x = x;
				player_pos.y = y;
				return (player_pos);
			}
			x++;
		}
		y++;
	}
	return (player_pos);
}

void	init_player(t_mlx_data *data)
{
	t_vect	player_pos;

	player_pos = get_player_pos(data->map->map);
	data->ray = malloc(sizeof(t_ray));
	data->ray->pos_x = player_pos.x;
	data->ray->pos_y = player_pos.y;
	data->ray->dir_x = -1;
	data->ray->dir_y = 0;
	get_player_dir(&data->ray->dir_x, &data->ray->dir_y, &player_pos,
			data->map->map);
	data->ray->plane_x = 0;
	data->ray->plane_y = 0.66;
}
