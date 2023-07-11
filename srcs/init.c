/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:13:45 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/11 17:28:51 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_mlx(t_mlx_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, SIZE_X, SIZE_Y, "cub3D");
	data->img_ptr = mlx_new_image(data->mlx_ptr, SIZE_X, SIZE_Y);
	data->addr = mlx_get_data_addr(data->img_ptr, &data->bits_pixel,
			&data->size_line, &data->endian);
}

int	init_key(t_mlx_data *data)
{
	data->key = malloc(sizeof(t_key));
	if (!data->key)
		return (1);
	data->key->mv_forward = 0;
	data->key->mv_backward = 0;
	data->key->mv_left = 0;
	data->key->mv_right = 0;
	data->key->rot_left = 0;
	data->key->rot_right = 0;
	return (0);
}
