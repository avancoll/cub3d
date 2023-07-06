/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:12:57 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/06 16:12:21 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static t_vect	map_size(char **map)
{
	t_vect	size;

	size.y = 0;
	size.x = 0;
	while (map && map[size.y])
		size.y++;
	while (map && map[0][size.x])
		size.x++;
	return (size);
}

int	map_check(char **map)
{
	int		x;
	int		y;
	t_vect	size;

	y = 0;
	size = map_size(map);
	while (map && map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((y == 0 || x == 0 || y == size.y || x == size.x)
				&& map[y][x] == '0')
				return (-1);
			else if (ft_strchr("0NSWE", map[y][x]) && (map[y][x - 1] == '2'
						|| map[y][x + 1] == '2' || map[y - 1][x] == '2' || map[y
						+ 1][x] == '2'))
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}
