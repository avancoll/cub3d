/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:15:42 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/13 15:25:56 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	display_error(t_mlx_data *data, int errnum, int fd)
{
	write(2, "Error\n", 6);
	if (errnum == 1)
		write(2, "Wrong number of arguments\n", 26);
	else if (errnum == 2)
		write(2, "Wrong file extension\n", 21);
	else if (errnum == 3 || errnum == 4)
		perror("cub3D");
	else if (errnum == 5)
		write(2, "Invalid map\n", 12);
	else if (errnum == 6)
		write(2, "Malloc failed\n", 14);
	else if (errnum == 7)
		write(1, "Bad xpm file\n", 13);
	if (data)
		free_all(data);
	if (fd != -1)
		close(fd);
	return (1);
}

int	ft_close(t_mlx_data *data)
{
	if (data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free_all(data);
	exit(0);
}

int	filename_checker(char *str)
{
	if (ft_strlen(str) > 4 && ft_strcmp(str + ft_strlen(str) - 4, ".cub"))
		return (1);
	return (0);
}

int	free_all(t_mlx_data *data)
{
	ft_t_map_free(data->map);
	if (data->key)
	{
		free(data->key);
		data->key = NULL;
	}
	if (data->ray)
	{
		free(data->ray);
		data->ray = NULL;
	}
	return (1);
}
