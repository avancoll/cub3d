/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 00:06:13 by jusilanc          #+#    #+#             */
/*   Updated: 2023/07/07 18:16:07 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "get_next_line.h"
# include "libft.h"
# include <stdio.h>

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
	char 			**img_data;
}					t_map;

void				ft_t_map_free(t_map *map);
t_map				*parser(int fd);
int					map_check(t_map *map);
int					check_parsing(t_map *map);

#endif
