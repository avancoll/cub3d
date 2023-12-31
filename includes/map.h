/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 00:06:13 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/13 14:43:20 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>

enum e_error
{
	OTHER_TPYE = 4,
	WRONG_MAP
};

typedef struct s_map
{
	char			*texture_no;
	char			*texture_so;
	char			*texture_we;
	char			*texture_ea;
	unsigned int	floor;
	unsigned int	ceiling;
	char			**map;
	int				x;
	int				y;
	void			**img_from_xpm;
	char			**img_data;
	int				tex_width;
	int				tex_height;
}					t_map;

unsigned int		color_converter(char *str);
void				ft_t_map_free(t_map *map);
void				color_converter_part(int *col_tmp, int *col, int *i,
						char **c);
int					parser(int fd, t_map *map, int ret);
int					data_color_filler(t_map *map, char **str_line);
int					map_check(t_map *map);
int					check_parsing(t_map *map);
int					data_filler(t_map *map, char **str_line);

int					map_part(char *line, char *line_tmp, int fd, t_list **lst);
int					header_part(char *line, char *line_tmp, int fd, t_map *map);
void				skip_empty_lines(char **line_tmp, char *line, int fd);
void				skip_empty_lines_map(char **line_tmp, char *line, int fd);

#endif
