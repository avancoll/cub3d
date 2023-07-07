/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:12:57 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/07 17:37:57 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	map_size(t_map *map)
{
	map->x = 0;
	map->y = 0;
	while (map && map->map[map->y])
		map->y++;
	while (map && map->map[0][map->x])
		map->x++;
}

int	map_check(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	map_size(map);
	while (map->map && map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if ((y == 0 || x == 0 || y == map->y || x == map->x) && map->map[y][x] == '0')
				return (-1);
			else if (ft_strchr("0NSWE", map->map[y][x]) && (map->map[y][x - 1] == '2'
						|| map->map[y][x + 1] == '2' || map->map[y - 1][x] == '2' || map->map[y + 1][x] == '2'))
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}
