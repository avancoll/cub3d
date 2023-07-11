/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:17:30 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/11 17:40:12 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	init_map(t_mlx_data *data)
{
	data->key = NULL;
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (-1);
	data->map->texture_no = NULL;
	data->map->texture_so = NULL;
	data->map->texture_we = NULL;
	data->map->texture_ea = NULL;
	data->map->floor = (255 << 24);
	data->map->ceiling = (255 << 24);
	data->map->map = NULL;
	data->map->img_from_xpm = NULL;
	data->map->img_data = NULL;
	return (0);
}

void	color_converter_part(int *col_tmp, int *col, int *i, char **c)
{
	*col_tmp = ft_atoi(c[*i]);
	if (*col_tmp > 255 || *col_tmp < 0 || *i > 2)
		*col = -1;
	if (*col != -1 && *i >= 0)
	{
		(*col) *= 256;
		(*col) += *col_tmp;
	}
	(*i)++;
}

unsigned int	color_converter(char *str)
{
	char	**c;
	int		col;
	int		col_tmp;
	int		i;

	i = 0;
	col = 0;
	c = ft_split(str, ',');
	if (!c)
		return (-1);
	while (col != -1 && c[i])
	{
		if (ft_strlen(c[i]) > 3 || !is_all_digit(c[i]) || ft_strlen(c[i]) == 0)
			col = -1;
		else
			color_converter_part(&col_tmp, &col, &i, c);
	}
	if (i < 3)
		col = -1;
	double_free(c);
	return (col);
}

int	data_color_filler(t_map *map, char **str_line)
{
	if (!ft_strcmp(str_line[0], "F"))
	{
		if (!(map->floor & (255 << 24)))
			return (-1);
		map->floor = color_converter(str_line[1]);
		if (map->floor == (unsigned int)-1)
			return (-1);
	}
	else if (!ft_strcmp(str_line[0], "C"))
	{
		if (!(map->ceiling & (255 << 24)))
			return (-1);
		map->ceiling = color_converter(str_line[1]);
		if (map->ceiling == (unsigned int)-1)
			return (-1);
	}
	return (0);
}

void	ft_t_map_free(t_map *map)
{
	free(map->texture_no);
	map->texture_no = NULL;
	free(map->texture_so);
	map->texture_so = NULL;
	free(map->texture_we);
	map->texture_we = NULL;
	free(map->texture_ea);
	map->texture_ea = NULL;
	double_free(map->map);
	map->map = NULL;
	free(map->img_from_xpm);
	map->img_from_xpm = NULL;
	free(map->img_data);
	map->img_data = NULL;
	free(map);
	map = NULL;
}
