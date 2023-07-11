/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:04:56 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/11 13:00:18 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	player_pos(char *map)
{
	int	x;
	int	pos;

	x = 0;
	pos = 0;
	while (map && map[x])
	{
		if (ft_strchr("NSWE", map[x]))
			pos++;
		else if (!ft_strchr("012NSWE", map[x]))
			pos += 10;
		x++;
	}
	return (pos);
}

static int	player_check(t_map *map)
{
	char	**map_cpy;
	int		y;
	int		ppos;

	y = 0;
	ppos = 0;
	map_cpy = ft_tabdup(map->map);
	if (!map_cpy)
		return (-1);
	while (map_cpy[y])
	{
		ppos += player_pos(map_cpy[y]);
		y++;
	}
	double_free(map_cpy);
	if (ppos == 0 || ppos > 1)
		return (-1);
	return (0);
}

static int	file_exist(t_map *map)
{
	int	fd[4];

	fd[0] = open(map->texture_no, O_RDONLY);
	fd[1] = open(map->texture_so, O_RDONLY);
	fd[2] = open(map->texture_ea, O_RDONLY);
	fd[3] = open(map->texture_we, O_RDONLY);
	if (fd[0] < 0 || fd[1] < 0 || fd[2] < 0 || fd[3] < 0)
		return (-1);
	return (0);
}

int	check_parsing(t_map *map)
{
	if (!map->texture_no || !map->texture_so || !map->texture_we
		|| !map->texture_ea || map->ceiling & (255 << 24)
		|| map->floor & (255 << 24))
		return (-1);
	if (player_check(map) == -1 || map_check(map) == -1
		|| file_exist(map) == -1)
		return (-1);
	return (0);
}
