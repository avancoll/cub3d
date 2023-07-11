/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:32:44 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/11 12:28:17 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_texture(t_mlx_data *data)
{
	void **const	img = malloc(sizeof(void *) * 4);

	img[0] = mlx_xpm_file_to_image(data->mlx_ptr, data->map->texture_no,
			&data->map->tex_width, &data->map->tex_height);
	img[1] = mlx_xpm_file_to_image(data->mlx_ptr, data->map->texture_so,
			&data->map->tex_width, &data->map->tex_height);
	img[2] = mlx_xpm_file_to_image(data->mlx_ptr, data->map->texture_we,
			&data->map->tex_width, &data->map->tex_height);
	img[3] = mlx_xpm_file_to_image(data->mlx_ptr, data->map->texture_ea,
			&data->map->tex_width, &data->map->tex_height);
	data->map->img_from_xpm = img;
}

void	get_texture_addr(t_mlx_data *data)
{
	int				i;
	char **const	img_data = malloc(sizeof(char *) * 4);

	i = 0;
	data->size_line = SIZE_X * 4;
	init_texture(data);
	while (i < 4)
	{
		img_data[i] = mlx_get_data_addr(data->map->img_from_xpm[i],
				&data->bits_pixel,
				&data->size_line,
				&data->endian);
		i++;
	}
	data->map->img_data = img_data;
}
