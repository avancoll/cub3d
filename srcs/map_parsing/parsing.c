/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:29:49 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/11 15:15:03 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

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
		ft_strreverse(map->map[i]);
		tmp_lst = tmp_lst->next;
		i++;
		map->map[i] = NULL;
	}
	ft_lstclear(&lst, free);
	map_replacer(map);
}

int	parser(int fd, t_map *map)
{
	char	*line;
	char	**temp;
	char	*line_tmp;
	int		i;
	t_list	*lst;

	i = 6;
	lst = NULL;
	if (!map || fd < 0)
		return (OTHER_TPYE);
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
			return (OTHER_TPYE);
		if (temp[2] || data_filler(map, temp) || data_color_filler(map, temp))
			return (WRONG_MAP);
		double_free(temp);
	}
	line = get_next_line(fd);
	line_tmp = ft_strtrim(line, "\n");
	if (!line_tmp)
		return (OTHER_TPYE);
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
		return (WRONG_MAP);
	return (0);
}
