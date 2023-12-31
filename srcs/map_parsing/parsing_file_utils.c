/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:02:16 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/13 14:56:56 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	skip_empty_lines(char **line_tmp, char *line, int fd)
{
	while (ft_strlen(*line_tmp) == 0)
	{
		free(*line_tmp);
		*line_tmp = NULL;
		line = get_next_line(fd);
		*line_tmp = ft_strtrim(line, "\n\t ");
		free(line);
		if (!*line_tmp)
			break ;
	}
}

void	skip_empty_lines_map(char **line_tmp, char *line, int fd)
{
	while (ft_strlen(*line_tmp) == 0)
	{
		free(*line_tmp);
		*line_tmp = NULL;
		line = get_next_line(fd);
		*line_tmp = ft_strtrim(line, "\n\t");
		free(line);
		if (!*line_tmp)
			break ;
	}
}

int	header_part(char *line, char *line_tmp, int fd, t_map *map)
{
	char	**temp;
	int		i;

	i = 6;
	while (i-- > 0)
	{
		line = get_next_line(fd);
		line_tmp = ft_strtrim(line, "\n ");
		free(line);
		skip_empty_lines(&line_tmp, line, fd);
		temp = ft_split(line_tmp, ' ');
		free(line_tmp);
		if (!temp)
			return (OTHER_TPYE);
		if (temp[2] || data_filler(map, temp) || data_color_filler(map, temp))
			return (WRONG_MAP);
		double_free(temp);
	}
	return (0);
}

int	map_part(char *line, char *line_tmp, int fd, t_list **lst)
{
	t_list	*tmp_lst;

	while (line_tmp)
	{
		tmp_lst = ft_lstnew(line_tmp);
		if (!tmp_lst)
		{
			ft_lstclear(lst, free);
			free(line_tmp);
			return (1);
		}
		ft_lstadd_back(lst, tmp_lst);
		line = get_next_line(fd);
		line_tmp = ft_strtrim(line, "\n");
		free(line);
	}
	return (0);
}
