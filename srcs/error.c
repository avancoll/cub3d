/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:15:42 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/11 17:16:23 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_close(t_mlx_data *data)
{
	if (data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}

int	filename_checker(char *str)
{
	if (ft_strlen(str) > 4)
	{
		if (ft_strcmp(str + ft_strlen(str) - 4, ".cub"))
		{
			write(2, "Error\nWrong file extension\n", 28);
			return (1);
		}
	}
	else
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
	return (1);
}
