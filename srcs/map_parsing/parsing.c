/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:29:49 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/04 15:49:01 by jusilanc         ###   ########.fr       */
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

static int	data_color_filler(t_map *map, char **str_line)
{
	if (ft_strcmp(str_line[0], "F"))
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

static void	double_free(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
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

static int	color_converter(char *str)
{
	char	**colors;
	int		col;
	int		i;

	i = 2;
	col = 0;
	colors = ft_split(str, ',');
	if (!colors)
		return (-1);
	if (ft_strlen(colors[0]) > 3 || ft_strlen(colors[1]) > 3
		|| ft_strlen(colors[2]) > 3 || !is_all_digit(colors[0])
		|| !is_all_digit(colors[1]) || !is_all_digit(colors[2]))
		col = -1;
	while (col != -1 && i >= 0)
	{
		col = ft_atoi(colors[i]);
		if (col > 255 || col < 0)
			col = -1;
		if (col != -1 && i > 0)
			col = col << 8;
		i--;
	}
	double_free(colors);
	return (col);
}

static int	data_filler(t_map *map, char **str_line)
{
	if (ft_strcmp(str_line[0], "NO"))
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
	return (0);
}

static void	map_filler(t_map *map, t_list *lst)
{
	t_list	*tmp_lst;
	int		max_len;
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
	map->map = (char **)malloc(sizeof(char *) * ft_lstsize(lst) + 1);
	if (!map->map)
		return ;
	tmp_lst = lst;
	while (tmp_lst)
	{
		map->map[i] = (char *)malloc(sizeof(char) * max_len + 1);
		ft_memset(map->map[i], '2', max_len);
		map->map[max_len] = 0;
		ft_memcpy(map->map[i], tmp_lst->content, ft_strlen(tmp_lst->content));
		tmp_lst = tmp_lst->next;
		i++;
	}
	map->map[i] = NULL;
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
	return (map);
}
