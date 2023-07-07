/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:29:49 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/07 17:52:58 by jusilanc         ###   ########.fr       */
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

static unsigned int	color_converter(char *str)
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
		{
			col_tmp = ft_atoi(c[i]);
			if (col_tmp > 255 || col_tmp < 0 || i > 2)
				col = -1;
			if (col != -1 && i >= 0)
			{
				col *= 256;
				col += col_tmp;
			}
			i++;
		}
	}
	if (i < 3)
		col = -1;
	double_free(c);
	return (col);
}

static int	data_color_filler(t_map *map, char **str_line)
{
	if (!ft_strcmp(str_line[0], "F"))
	{
		if (!(map->floor & (255 << 24)))
			return (-1);
		map->floor = color_converter(str_line[1]);
	}
	else if (!ft_strcmp(str_line[0], "C"))
	{
		if (!(map->ceiling & (255 << 24)))
			return (-1);
		map->ceiling = color_converter(str_line[1]);
	}
	return (0);
}

void	ft_t_map_free(t_map *map)
{
	free(map->texture_no);
	free(map->texture_so);
	free(map->texture_we);
	free(map->texture_ea);
	double_free(map->map);
	free(map);
}

static int	data_filler(t_map *map, char **str_line)
{
	if (!ft_strcmp(str_line[0], "NO"))
	{
		if (map->texture_no)
			return (-1);
		map->texture_no = ft_strdup(str_line[1]);
	}
	else if (!ft_strcmp(str_line[0], "SO"))
	{
		if (map->texture_so)
			return (-1);
		map->texture_so = ft_strdup(str_line[1]);
	}
	else if (!ft_strcmp(str_line[0], "WE"))
	{
		if (map->texture_we)
			return (-1);
		map->texture_we = ft_strdup(str_line[1]);
	}
	else if (!ft_strcmp(str_line[0], "EA"))
	{
		if (map->texture_ea)
			return (-1);
		map->texture_ea = ft_strdup(str_line[1]);
	}
	return (0);
}

static void	map_replacer(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == ' ')
				map->map[y][x] = '2';
			x++;
		}
		y++;
	}
}

static void	map_filler(t_map *map, t_list *lst)
{
	t_list	*tmp_lst;
	size_t	max_len;
	int		i;

	i = 0;
	tmp_lst = lst;
	max_len = 0;
	while (tmp_lst)
	{
		if (ft_strlen(tmp_lst->content) > max_len)
			max_len = ft_strlen(tmp_lst->content);
		tmp_lst = tmp_lst->next;
	}
	map->map = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!map->map)
		return ;
	tmp_lst = lst;
	while (tmp_lst)
	{
		map->map[i] = (char *)malloc(sizeof(char) * (max_len + 1));
		ft_memset(map->map[i], '2', max_len);
		map->map[i][max_len] = 0;
		ft_memcpy(map->map[i], tmp_lst->content, ft_strlen(tmp_lst->content));
		tmp_lst = tmp_lst->next;
		i++;
	}
	map->map[i] = NULL;
	map_replacer(map);
}

t_map	*parser(int fd)
{
	t_map	*map;
	char	*line;
	char	**temp;
	char	*line_tmp;
	int		i;
	t_list	*lst;

	i = 6;
	lst = NULL;
	map = map_init();
	if (!map || fd < 0)
	{
		perror("cub3D");
		return (NULL);
	}
	while (i-- > 0)
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
		if (temp[2] || data_filler(map, temp) || data_color_filler(map, temp))
		{
			write(2, "ERROR MAP\n", 10);
			ft_t_map_free(map);
			return (NULL);
		}
		double_free(temp);
	}
	line = get_next_line(fd);
	line_tmp = ft_strtrim(line, "\n");
	if (!line_tmp)
	{
		write(2, "ERROR MAP\n", 10);
		ft_t_map_free(map);
		return (NULL);
	}
	free(line);
	while (ft_strlen(line_tmp) == 0)
	{
		free(line_tmp);
		line = get_next_line(fd);
		line_tmp = ft_strtrim(line, "\n");
		free(line);
		if (!line_tmp)
			break ;
	}
	while (line_tmp)
	{
		ft_lstadd_back(&lst, ft_lstnew(line_tmp));
		line = get_next_line(fd);
		line_tmp = ft_strtrim(line, "\n");
		free(line);
	}
	map_filler(map, lst);
	if (check_parsing(map) == -1)
	{
		write(2, "ERROR MAP\n", 10);
		ft_t_map_free(map);
		return (NULL);
	}
	return (map);
}
