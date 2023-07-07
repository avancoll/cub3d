/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:32:44 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/07 19:18:50 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_texture(t_mlx_data *data)
{
	void	*img[4];
	int		s;

	s = 64;
	img[0] = mlx_xpm_file_to_image(data->mlx_ptr, data->map->texture_no, &s,
			&s);
	img[1] = mlx_xpm_file_to_image(data->mlx_ptr, data->map->texture_so, &s,
			&s);
	img[2] = mlx_xpm_file_to_image(data->mlx_ptr, data->map->texture_we, &s,
			&s);
	img[3] = mlx_xpm_file_to_image(data->mlx_ptr, data->map->texture_ea, &s,
			&s);
	data->map->img_from_xpm = img;
}

void	get_texture_addr(t_mlx_data *data)
{
	char	*img_data[4];
	int		i;

	i = 0;
	init_texture(data);
	while (i < 4)
	{
		img_data[i] = mlx_get_data_addr(data->map->img_from_xpm[i], &data->bits_pixel,
				&data->size_line, &data->endian);
		i++;
	}
	data->map->img_data = img_data;
}
