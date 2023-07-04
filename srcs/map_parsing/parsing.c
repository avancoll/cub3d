/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:29:49 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/04 13:51:12 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static t_map	*map_init(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->texture_no = NULL;
	map->texture_so = NULL;
	map->texture_we = NULL;
	map->texture_ea = NULL;
	map->floor = (255 << 24);
	map->ceiling = (255 << 24);
	map->map = NULL;
	return (map);
}

static void	double_free(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

static int	color_converter(char *str)
{
	char	**colors;
	int		col;

	col = 0;
	colors = ft_split(str, ',');
	if (!colors)
		return (-1);
	if (ft_strlen(colors[0]) > 3 || ft_strlen(colors[1]) > 3
		|| ft_strlen(colors[2]) > 3)
		col = -1;
	if (col != -1)
		col = ft_atoi(colors[2]);
	if (col > 255 || col < 0)
		col = -1;
	if (col != -1)
		col = col << 8;
	if (col != -1)
		col = ft_atoi(colors[1]);
	if (col > 255 || col < 0)
		col = -1;
	if (col != -1)
		col = col << 8;
	if (col != -1)
		col = ft_atoi(colors[0]);
	if (col > 255 || col < 0)
		col = -1;
	double_free(colors);
	return (col);
}

static int	data_filler(t_map *map, char **str_line)
{
	if (str_line[2])
		return (-1);
	else if (ft_strcmp(str_line[0], "NO"))
	{
		if (map->texture_no)
			return (-1);
		map->texture_no = ft_strdup(str_line[1]);
	}
	else if (ft_strcmp(str_line[0], "SO"))
	{
		if (map->texture_so)
			return (-1);
		map->texture_so = ft_strdup(str_line[1]);
	}
	else if (ft_strcmp(str_line[0], "WE"))
	{
		if (map->texture_we)
			return (-1);
		map->texture_we = ft_strdup(str_line[1]);
	}
	else if (ft_strcmp(str_line[0], "EA"))
	{
		if (map->texture_ea)
			return (-1);
		map->texture_ea = ft_strdup(str_line[1]);
	}
	else if (ft_strcmp(str_line[0], "F"))
	{
		if (!(map->floor & (255 << 24)))
			return (-1);
		map->floor = color_converter(str_line[1]);
	}
	else if (ft_strcmp(str_line[0], "C"))
	{
		if (!(map->ceiling & (255 << 24)))
			return (-1);
		map->ceiling = color_converter(str_line[1]);
	}
	return (0);
}

t_map	*parser(int fd)
{
	t_map	*map;
	char	*line;
	char	**temp;
	char	*line_tmp;
	int		i;

	i = 6;
	map = map_init();
	if (!map)
		return (NULL);
	while (i-- >= 0)
	{
		line = get_next_line(fd);
		line_tmp = ft_strtrim(line, "\n ");
		free(line);
		while (ft_strlen(line_tmp) == 0)
		{
			free(line_tmp);
			line = get_next_line(fd);
			line_tmp = ft_strtrim(line, "\n ");
			free(line);
			if (!line_tmp)
				break ;
		}
		temp = ft_split(line_tmp, ' ');
		free(line_tmp);
		if (!temp)
			return (NULL);
		if (data_filler(map, temp))
		{
			write(2, "ERROR MAP\n", 10);
			// need to free t_map;
			return (NULL);
		}
		double_free(temp);
	}
	return (map);
}
