/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:32:44 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/12 17:43:32 by jusilanc         ###   ########.fr       */
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
	if (!img[0] || !img[1] || !img[2] || !img[3])
	{
		free(img);
		write(1, "Error\nBad xpm file\n", 19);
		data->map->img_from_xpm = NULL;
	}
	else
		data->map->img_from_xpm = img;
}

void	get_texture_addr(t_mlx_data *data)
{
	int				i;
	char **const	img_data = malloc(sizeof(char *) * 4);

	i = 0;
	data->size_line = SIZE_X * 4;
	init_texture(data);
	while (i < 4 && data->map->img_from_xpm && data->map->img_from_xpm[i])
	{
		img_data[i] = mlx_get_data_addr(data->map->img_from_xpm[i],
				&data->bits_pixel,
				&data->size_line,
				&data->endian);
		i++;
	}
	if (!data->map->img_from_xpm)
	{
		free(img_data);
		data->map->img_data = NULL;
	}
	else
		data->map->img_data = img_data;
}
